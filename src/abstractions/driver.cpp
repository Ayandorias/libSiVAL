/*
 * libSiVAL
 *
 * Copyright (C) since 2025 Bruno Pierucki
 *
 * Author: Bruno Pierucki <b.pierucki@gmx.de>
 */

//// begin includes
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
//// end includes

//// begin system includes
//// end system includes

//// begin project specific includes
#include <sival/abstractions/driver.hpp>
#include "sival/utils/siconverter.hpp"
//// end project specific includes

//// begin using namespaces
using namespace SiVAL::Utils;
using json = nlohmann::json;
//// end using namespaces

//// begin global definition
//// end global definition

//// begin extern declaration
//// end extern declaration

//// begin static definitions
//// end static definitions

//// begin static functions
//// end static functions

namespace SiVAL {

//// begin public member methods
AbstractDriver::AbstractDriver(nlohmann::json &data) {
    // Wird nicht mehr benötigt, da das ganze jetzt über die DriverFactory erledigt wird.
    //
    // std::ifstream file(json);
    // if (!file.is_open()) {
    //     throw std::runtime_error("Cannot open JSON file: " + json);
    // }
    // nlohmann::json data;
    // file >> data;

    // Helper lambda to safely get a value-unit pair and convert it
    auto getConvertedValue = [&](const nlohmann::json& parent, const std::string& key, auto converter) -> double {
        const auto& obj = parent.at(key);
        return converter(obj.at("value").get<double>(), obj.at("unit").get<std::string>());
    };

    // Helper for optional value-unit pairs
    auto getOptionalConvertedValue = [&](const nlohmann::json& parent, const std::string& key, auto converter) -> std::optional<double> {
        if (!parent.contains(key) || parent.at(key).is_null()) {
            return std::nullopt;
        }
        const auto& obj = parent.at(key);
        return converter(obj.at("value").get<double>(), obj.at("unit").get<std::string>());
    };

    // --- Step 1: Read all fundamental, non-calculable parameters ---
    // If any of these are missing, an exception is thrown and the object is not created.

    // General Info
    const auto& gi = data.at("general_info");
    m_uuid = gi.at("uuid").get<std::string>();
    m_brand = gi.at("brand").get<std::string>();
    m_manufacturer = gi.at("manufacturer").get<std::string>();
    m_providedby = gi.at("providedby").get<std::string>();
    m_comment = gi.at("comment").get<std::string>();
    m_model = gi.at("model").get<std::string>();
    m_indexed = gi.at("indexed").get<bool>();
    m_speaker_type = gi.value("speaker_type", "");

    // Fundamental Electrical Parameters
    const auto& ep = data.at("electrical_parameters");
    m_re = ep.at("re").at("value").get<double>();
    m_bl = ep.at("bl").at("value").get<double>();

    // Other Electrical Parameters (read directly)
    m_impedance = ep.at("impedance").at("value").get<double>();
    m_le = ep.at("le").at("value").get<double>();
    m_znom = ep.at("znom").at("value").get<double>();
    m_pe = ep.at("pe").at("value").get<double>();
    m_pmax = ep.at("pmax").at("value").get<double>();
    m_motor_constant = ep.at("motor_constant").at("value").get<double>();
    m_flux_density = ep.at("flux_density").at("value").get<double>();

    // Fundamental Thiele-Small Parameters
    const auto& tsp = data.at("thiele_small_parameters");
    m_fs = tsp.at("fs").at("value").get<double>();
    m_qms = tsp.at("qms").at("value").get<double>();
    m_mms_kg = getConvertedValue(tsp, "mms", SIConverter::toMass);
    m_sd_m2 = getConvertedValue(tsp, "sd", SIConverter::toArea);

    // Non-fundamental but directly read parameters
    m_mmd_kg = getConvertedValue(tsp, "mmd", SIConverter::toMass);
    m_rms = tsp.at("rms").at("value").get<double>();
    m_xmax_m = getOptionalConvertedValue(tsp, "xmax", SIConverter::toLength);
    m_xlim_m = getOptionalConvertedValue(tsp, "xlim", SIConverter::toLength);

    // Physical Dimensions
    const auto& pd = data.at("physical_dimensions");
    m_nominal_diameter = pd.at("nominal_diameter").get<std::string>();
    m_vc_diameter_m = getConvertedValue(pd, "vc_diameter", SIConverter::toLength);
    m_winding_height_m = getConvertedValue(pd, "winding_height", SIConverter::toLength);
    m_air_gap_height_m = getConvertedValue(pd, "air_gap_height", SIConverter::toLength);
    m_effective_diameter_m = getConvertedValue(pd, "effective_diameter", SIConverter::toLength);
    m_baffle_cutout_diameter_m = getConvertedValue(pd, "baffle_cutout_diameter", SIConverter::toLength);
    m_volume_occupied_m3 = getConvertedValue(pd, "volume_occupied", SIConverter::toVolume);
    m_net_weight_kg = getConvertedValue(pd, "net_weight", SIConverter::toMass);
    m_material = pd.at("material").get<std::string>();

    // --- Step 2: Read or calculate derivable parameters ---
    // The order is important due to dependencies.

    if (tsp.contains("qes")) {
        m_qes = tsp.at("qes").at("value").get<double>();
    } else {
        m_qes = calculateQes();
    }

    if (tsp.contains("qts")) {
        m_qts = tsp.at("qts").at("value").get<double>();
    } else {
        m_qts = calculateQts();
    }

    if (tsp.contains("cms")) {
        m_cms = tsp.at("cms").at("value").get<double>();
    } else {
        m_cms = calculateCms();
    }

    if (tsp.contains("stiffness")) {
        m_stiffness = tsp.at("stiffness").at("value").get<double>();
    } else {
        m_stiffness = calculateKms();
    }

    if (tsp.contains("vas")) {
        m_vas_m3 = getConvertedValue(tsp, "vas", SIConverter::toVolume);
    } else {
        m_vas_m3 = calculateVas();
    }

    if (tsp.contains("vd")) {
        m_vd_m3 = getOptionalConvertedValue(tsp, "vd", SIConverter::toVolume);
    } else {
        m_vd_m3 = calculateVd();
    }

    if (ep.contains("sensitivity")) {
        m_sensitivity = ep.at("sensitivity").at("value").get<double>();
    } else {
        m_sensitivity = calculateSensitivity();
    }
}

AbstractDriver::~AbstractDriver() = default;

const std::string& AbstractDriver::uuid() const
{
    return m_uuid;
}

const std::string& AbstractDriver::brand() const
{
    return m_brand;
}

const std::string& AbstractDriver::manufacturer() const
{
    return m_manufacturer;
}

const std::string& AbstractDriver::providedBy() const
{
    return m_providedby;
}

const std::string& AbstractDriver::comment() const
{
    return m_comment;
}

const std::string& AbstractDriver::model() const
{
    return m_model;
}

bool AbstractDriver::indexed() const
{
    return m_indexed;
}

const std::string& AbstractDriver::speakerType() const
{
    return m_speaker_type;
}

double AbstractDriver::impedance() const
{
    return m_impedance;
}

double AbstractDriver::sensitivity() const
{
    return m_sensitivity;
}

double AbstractDriver::re() const
{
    return m_re;
}

double AbstractDriver::le() const
{
    return m_le;
}

double AbstractDriver::znom() const
{
    return m_znom;
}

double AbstractDriver::pe() const
{
    return m_pe;
}

double AbstractDriver::pmax() const
{
    return m_pmax;
}

double AbstractDriver::bl() const
{
    return m_bl;
}

double AbstractDriver::motorConstant() const
{
    return m_motor_constant;
}

double AbstractDriver::fluxDensity() const
{
    return m_flux_density;
}

double AbstractDriver::fs() const
{
    return m_fs;
}

double AbstractDriver::qms() const
{
    return m_qms;
}

double AbstractDriver::qes() const
{
    return m_qes;
}

double AbstractDriver::qts() const
{
    return m_qts;
}

double AbstractDriver::mms() const
{
    return m_mms_kg;
}

double AbstractDriver::mmd() const
{
    return m_mmd_kg;
}

double AbstractDriver::stiffness() const
{
    return m_stiffness;
}

double AbstractDriver::cms() const
{
    return m_cms;
}

double AbstractDriver::vas() const
{
    return m_vas_m3;
}

double AbstractDriver::rms() const
{
    return m_rms;
}

double AbstractDriver::sd() const
{
    return m_sd_m2;
}

std::optional<double> AbstractDriver::xmax() const
{
    return m_xmax_m;
}

std::optional<double> AbstractDriver::xlim() const
{
    return m_xlim_m;
}

std::optional<double> AbstractDriver::vd() const
{
    return m_vd_m3;
}

const std::string& AbstractDriver::nominalDiameter() const
{
    return m_nominal_diameter;
}

double AbstractDriver::vcDiameter() const
{
    return m_vc_diameter_m;
}

double AbstractDriver::windingHeight() const
{
    return m_winding_height_m;
}

double AbstractDriver::airGapHeight() const
{
    return m_air_gap_height_m;
}

double AbstractDriver::effectiveDiameter() const
{
    return m_effective_diameter_m;
}

double AbstractDriver::baffleCutoutDiameter() const
{
    return m_baffle_cutout_diameter_m;
}

double AbstractDriver::volumeOccupied() const
{
    return m_volume_occupied_m3;
}

double AbstractDriver::netWeight() const
{
    return m_net_weight_kg;
}

const std::string& AbstractDriver::material() const
{
    return m_material;
}
//// end public member methods

//// begin public member methods (internal use only)
//// end public member methods (internal use only)

//// begin protected member methods
//// end protected member methods

//// begin protected member methods (internal use only)
double AbstractDriver::calculateQes() const {
    if (m_bl == 0) return 0; // Avoid division by zero
    return (2 * SiVAL::PI * m_fs * m_mms_kg * m_re) / (m_bl * m_bl);
}

double AbstractDriver::calculateQts() const {
    if ((m_qms + m_qes) == 0) return 0; // Use the now-guaranteed-to-be-set m_qes
    return (m_qms * m_qes) / (m_qms + m_qes);
}

double AbstractDriver::calculateCms() const {
    const double term = 2 * SiVAL::PI * m_fs;
    if (term == 0 || m_mms_kg == 0) return 0; // Avoid division by zero
    return 1.0 / ((term * term) * m_mms_kg);
}

double AbstractDriver::calculateKms() const {
    const double term = 2 * SiVAL::PI * m_fs;
    return (term * term) * m_mms_kg;
}

double AbstractDriver::calculateVas() const {
    return RHO0 * SiVAL::C_SOUND * SiVAL::C_SOUND * m_sd_m2 * m_sd_m2 * m_cms; // Use the now-guaranteed-to-be-set m_cms
}

std::optional<double> AbstractDriver::calculateVd() const {
    if (!m_xmax_m.has_value()) {
        return std::nullopt;
    }
    return m_sd_m2 * m_xmax_m.value();
}

double AbstractDriver::calculateSensitivity() const {
    if (SiVAL::C_SOUND == 0 || m_qes == 0) return 0; // Avoid division by zero

    const double eta0 = (4 * SiVAL::PI * SiVAL::PI * std::pow(m_fs, 3) * m_vas_m3) / (std::pow(SiVAL::C_SOUND, 3) * m_qes);

    if (eta0 <= 0) return 0; // Logarithm is undefined for non-positive numbers

    return 112.0 + 10.0 * std::log10(eta0);
}
//// end protected member methods (internal use only)

//// begin private member methods
//// end private member methods

} // namespace SiVAL



