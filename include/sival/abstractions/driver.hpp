#pragma once

/*
 * libSiVAL
 *
 * Copyright (C) since 2025 Bruno Pierucki
 *
 * Author: Bruno Pierucki <b.pierucki@gmx.de>
 *
 */
//// begin system includes
#include <string>
#include <optional>
#include <nlohmann/json.hpp>
//// end system includes

//// begin project specific includes
#include <sival/libsival.hpp>
//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin forward declarations
//// end forward declarations

//// begin extern declaration
//// end extern declaration

namespace SiVAL {
/**
 * @class AbstractDriver
 *
 * @brief Represents the data of a speaker driver, loaded from a JSON file.
 *
 * This class is designed to provide structured access to the technical specifications
 * of a speaker driver, based on a specific JSON schema. The primary focus is on the
 * unambiguous representation of measured values by explicitly including their units,
 * which is essential for automated processing and correct data conversion.
 *
 * The class follows an "eager loading" pattern. Upon construction, it reads a specified
 * JSON file, parses the data, and stores it internally. All values with units are
 * immediately converted to the appropriate SI standard for internal consistency and
 * fast retrieval. The class is designed to be read-only after construction.
 *
 * @section schema JSON-Schema for Loudspeaker Driver Specifications
 *
 * This JSON schema is used for the structured collection of technical data for
 * loudspeaker drivers (chassis).
 *
 * @code{.json}
 * {
 * "$schema": "http://json-schema.org/draft-04/schema#",
 * "type": "object",
 * "properties": {
 * "general_info": {
 * "type": "object",
 * "description": "General and identifying information about the speaker driver.",
 * "properties": {
 * "uuid": { "type": "string" }, "brand": { "type": "string" }, "manufacturer": { "type": "string" },
 * "providedby": { "type": "string" }, "comment": { "type": "string" }, "model": { "type": "string" },
 * "indexed": { "type": "boolean" }, "speaker_type": { "type": "string" }
 * },
 * "required": ["uuid", "brand", "manufacturer", "providedby", "comment", "model", "indexed"]
 * },
 * "electrical_parameters": {
 * "type": "object",
 * "description": "Electrical characteristics of the speaker driver.",
 * "properties": {
 * "impedance": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "sensitivity": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "re": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "le": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "znom": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "pe": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "pmax": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "bl": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "motor_constant": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "flux_density": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] }
 * },
 * "required": ["impedance", "sensitivity", "re", "le", "znom", "pe", "pmax", "bl", "motor_constant", "flux_density"]
 * },
 * "thiele_small_parameters": {
 * "type": "object",
 * "description": "Thiele-Small (T-S) parameters for driver performance analysis.",
 * "properties": {
 * "fs": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "qms": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "qes": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "qts": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "mms": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "mmd": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "stiffness": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "cms": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "vas": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "rms": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "sd": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "xmax": { "type": ["object", "null"], "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "xlim": { "type": ["object", "null"], "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "vd": { "type": ["object", "null"], "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] }
 * },
 * "required": ["fs", "qms", "qes", "qts", "mms", "mmd", "stiffness", "cms", "vas", "rms", "sd", "xmax", "xlim", "vd"]
 * },
 * "physical_dimensions": {
 * "type": "object",
 * "description": "Physical dimensions and construction details.",
 * "properties": {
 * "vc_diameter": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "winding_height": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "air_gap_height": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "effective_diameter": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "nominal_diameter": { "type": "string" },
 * "baffle_cutout_diameter": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "volume_occupied": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "net_weight": { "type": "object", "properties": { "value": { "type": "number" }, "unit": { "type": "string" } }, "required": ["value", "unit"] },
 * "material": { "type": "string" }
 * },
 * "required": ["vc_diameter", "winding_height", "air_gap_height", "effective_diameter", "nominal_diameter", "baffle_cutout_diameter", "volume_occupied", "net_weight", "material"]
 * }
 * }
 * }
 * @endcode
 *
 * ### Explanation of the Main Objects
 *
 * 1.  **`general_info`**: This section serves for the administrative identification of the
 * driver and captures metadata such as origin, model, and driver type.
 *
 * 2.  **`electrical_parameters`**: Here, the electrical characteristics of the voice coil
 * and motor system are documented, which define the interaction with the amplifier.
 *
 * 3.  **`thiele_small_parameters`**: This block contains the acoustic and mechanical
 * parameters for calculating and simulating the low-frequency performance in an enclosure.
 *
 * 4.  **`physical_dimensions`**: This section captures the geometric dimensions and material
 * properties of the driver for the mechanical construction of enclosures.
 *
 * ### Important Note on Numerical Convention (JSON Standard)
 *
 * The JSON specification requires the use of the English standard for numerical values.
 * Deviations will lead to parser errors.
 * - **Decimal Separator**: A period (`.`) must be used. Correct: `"value": 1.5`
 * - **Thousands Separator**: Thousands separators must not be used. Correct: `"value": 1200`
 *
 * ### Detailed Parameters and Units
 *
 * All quantitative parameters use the structure `{"value": number, "unit": "string"}`.
 *
 * #### Electrical Parameters (`electrical_parameters`)
 *
 * | Parameter        | Description                    | Possible JSON Units | Unit Meaning                      | SI Unit (Returned by Class) |
 * | :--------------- | :----------------------------- | :------------------ | :-------------------------------- | :-------------------------- |
 * | `impedance`      | Nominal impedance (Z).         | `Ohm`               | **Ohm** (Ω)                       | **Ohm** (Ω)                 |
 * | `sensitivity`    | Characteristic SPL.            | `dB`                | **Decibel** | **Decibel** (dB)            |
 * | `re`             | DC resistance (Re).            | `Ohm`               | **Ohm** (Ω)                       | **Ohm** (Ω)                 |
 * | `le`             | Inductance (Le).               | `H`, `mH`           | **Henry, Millihenry** | **Henry** (H)               |
 * | `znom`           | Nominal impedance (Znom).      | `Ohm`               | **Ohm** (Ω)                       | **Ohm** (Ω)                 |
 * | `pe`             | Nominal power handling (RMS).  | `W`                 | **Watt** | **Watt** (W)                |
 * | `pmax`           | Maximum power handling.        | `W`                 | **Watt** | **Watt** (W)                |
 * | `bl`             | Force factor (B*l).            | `NA`, `Tm`          | **Newton per Ampere, Tesla-Meter** | **Tesla-meter** (Tm)        |
 * | `motor_constant` | Motor constant (Bl/√Re).       | `N_sqrtW`           | **Newton per square-root-Watt** | **N/√W** |
 * | `flux_density`   | Magnetic flux density.         | `T`, `G`            | **Tesla, Gauss** | **Tesla** (T)               |
 *
 * #### Thiele-Small Parameters (`thiele_small_parameters`)
 *
 * | Parameter   | Description                        | Possible JSON Units             | Unit Meaning                                   | SI Unit (Returned by Class) |
 * | :---------- | :--------------------------------- | :------------------------------ | :--------------------------------------------- | :-------------------------- |
 * | `fs`        | Resonance frequency (fs).          | `Hz`, `kHz`                     | **Hertz, Kilohertz** | **Hertz** (Hz)              |
 * | `qms`, etc. | Q-factors (Qms, Qes, Qts).         | `(dimensionless)`               | **(no unit)** | **(dimensionless)** |
 * | `mms` / `mmd`| Moving mass (Mms/Mmd).            | Metric: `kg`, `g` <br> Imperial: `oz` | **Kilogram, Gram, Ounce** | **Kilogram** (kg)           |
 * | `stiffness` | Spring stiffness (KMS).            | Metric: `N_m`, `N_mm` <br> Imperial: `lbf_in` | **Newton per meter, Newton per millimeter, Pound-force per inch** | **Newton/meter** (N/m)      |
 * | `cms`       | Compliance (CMS).                  | Metric: `m_N`, `um_N` <br> Imperial: `in_lbf` | **Meter per Newton, Micrometer per Newton, Inch per Pound-force** | **Meter/Newton** (m/N)      |
 * | `vas`       | Equivalent air volume (VAS).       | Metric: `m3`, `dm3`, `cm3`, `L`, `l` <br> Imperial: `ft3`, `in3` | **Cubic meter, Cubic decimeter (Liter), Cubic centimeter, Liter, Cubic foot, Cubic inch** | **Cubic meter** (m³)      |
 * | `rms`       | Mechanical resistance (RMS).       | `Ns_m`                          | **Newton-second per meter** | **Ns/m** |
 * | `sd`        | Effective diaphragm area (SD).     | Metric: `m2`, `cm2` <br> Imperial: `in2`, `ft2` | **Square meter, Square centimeter, Square inch, Square foot** | **Square meter** (m²)       |
 * | `xmax`/`xlim`| Linear/Mechanical excursion.      | Metric: `m`, `cm`, `mm` <br> Imperial: `in`, `ft` | **Meter, Centimeter, Millimeter, Inch, Foot** | **Meter** (m)               |
 * | `vd`        | Max. displacement volume (VD).     | Metric: `m3`, `dm3`, `cm3`, `L`, `l` <br> Imperial: `in3`, `ft3` | **Cubic meter, Cubic decimeter (Liter), Cubic centimeter, Liter, Cubic inch, Cubic foot** | **Cubic meter** (m³)      |
 *
 * #### Physical Dimensions (`physical_dimensions`)
 *
 * | Parameter        | Description                        | Possible JSON Units             | Unit Meaning                              | SI Unit (Returned by Class) |
 * | :--------------- | :--------------------------------- | :------------------------------ | :---------------------------------------- | :-------------------------- |
 * | `vc_diameter` etc. | Diameters & Heights.             | Metric: `m`, `cm`, `mm` <br> Imperial: `in`, `ft` | **Meter, Centimeter, Millimeter, Inch, Foot** | **Meter** (m)               |
 * | `nominal_diameter` | Nominal diameter string.         | `(string)`                      | **(no unit)** | **(string)** |
 * | `volume_occupied`| Volume displaced by driver.        | Metric: `m3`, `dm3`, `cm3`, `L`, `l` <br> Imperial: `ft3`, `in3` | **Cubic meter, Cubic decimeter (Liter), Cubic centimeter, Liter, Cubic foot, Cubic inch** | **Cubic meter** (m³)      |
 * | `net_weight`     | Net weight of the driver.          | Metric: `kg`, `g` <br> Imperial: `lb`, `oz` | **Kilogram, Gram, Pound, Ounce** | **Kilogram** (kg)           |
 * | `material`       | Material description.              | `(string)`                      | **(no unit)** | **(string)** |
 *
 */
class LIB_SIVAL_EXPORT AbstractDriver
{

    //// begin public member methods
public:
    /**
     * @brief Constructor that loads speaker data from a JSON file.
     * @details This constructor reads a JSON file according to the class schema. It
     * identifies fundamental parameters and attempts to read or calculate derivable
     * parameters to ensure a complete and consistent object state upon creation.
     * @param jsonFilePath The path to the JSON file containing the speaker data.
     * @throws std::runtime_error If the file cannot be opened.
     * @throws nlohmann::data::parse_error If the JSON is malformed.
     * @throws nlohmann::data::out_of_range If a required *fundamental* JSON field is missing.
     * @throws nlohmann::data::type_error If a JSON field has the wrong type.
     */
    explicit AbstractDriver(nlohmann::json &data);

    /**
     * @brief Default destructor.
     */
    ~AbstractDriver();

    // --- General Info Accessors ---

    /** * @brief Returns the unique identifier (UUID) of the driver.
     * @details This is a string used for unique identification in databases or collections.
     * @return const std::string& The UUID.
     */
    const std::string& uuid() const;

    /** * @brief Returns the brand name of the speaker driver.
     * @details Example: "Scan-Speak", "Peerless", "Dayton Audio".
     * @return const std::string& The brand name.
     */
    const std::string& brand() const;

    /** * @brief Returns the manufacturer of the speaker driver.
     * @details Can be the same as the brand, or a parent company.
     * @return const std::string& The manufacturer name.
     */
    const std::string& manufacturer() const;

    /** * @brief Returns the source of the data.
     * @details Indicates who provided the measurement data, e.g., "Manufacturer", "Hifi-Selbstbau".
     * @return const std::string& The data provider.
     */
    const std::string& providedBy() const;

    /** * @brief Returns any user-defined comments about the driver.
     * @return const std::string& The comment string.
     */
    const std::string& comment() const;

    /** * @brief Returns the model name or number of the driver.
     * @details Example: "18W/8531G00", "RSS210HO-4".
     * @return const std::string& The model name.
     */
    const std::string& model() const;

    /** * @brief Returns whether the driver is indexed in a database.
     * @return bool True if indexed, false otherwise.
     */
    bool indexed() const;

    /** * @brief Returns the type of the driver.
     * @details Example: "Woofer", "Midrange", "Tweeter", "Fullrange".
     * @return const std::string& The driver type.
     */
    const std::string& speakerType() const;

    // --- Electrical Parameter Accessors ---

    /** * @brief Returns the nominal impedance (Z) in Ohms.
     * @details This is the rated impedance, typically 4 or 8 Ohms, used for matching with amplifiers.
     * @return double The nominal impedance in Ohms.
     */
    double impedance() const;

    /** * @brief Returns the characteristic sensitivity in dB.
     * @details Typically measured at 1 Watt / 1 meter or 2.83 Volts / 1 meter. It indicates how efficiently the driver converts power to sound.
     * @return double The sensitivity in dB.
     */
    double sensitivity() const;

    /** * @brief Returns the DC resistance (Re) of the voice coil in Ohms.
     * @details This is a fundamental parameter for calculating electrical damping (Qes).
     * @return double The DC resistance in Ohms.
     */
    double re() const;

    /** * @brief Returns the voice coil inductance (Le) in Henry.
     * @details Le influences the high-frequency response of the driver.
     * @return double The inductance in Henry.
     */
    double le() const;

    /** * @brief Returns the nominal impedance (Znom) in Ohms. (Often same as `impedance`).
     * @return double The Znom value in Ohms.
     */
    double znom() const;

    /** * @brief Returns the nominal power handling (Pe) in Watts (RMS).
     * @details Represents the continuous power the driver can handle without damage.
     * @return double The nominal power handling in Watts.
     */
    double pe() const;

    /** * @brief Returns the maximum power handling (Pmax) in Watts.
     * @details Represents the short-term peak power the driver can handle.
     * @return double The maximum power handling in Watts.
     */
    double pmax() const;

    /** * @brief Returns the force factor (Bl) in Tesla-meters (Tm).
     * @details A key motor parameter representing the magnetic field strength in the gap (B) multiplied by the length of the voice coil wire in that field (l). Essential for calculating Qes.
     * @return double The force factor in Tm.
     */
    double bl() const;

    /** * @brief Returns the motor constant in N/√W.
     * @details Indicates motor efficiency (Bl/√Re).
     * @return double The motor constant.
     */
    double motorConstant() const;

    /** * @brief Returns the magnetic flux density in the voice coil gap in Tesla (T).
     * @return double The flux density in Tesla.
     */
    double fluxDensity() const;

    // --- Thiele-Small Parameter Accessors ---

    /** * @brief Returns the free-air resonance frequency (Fs) in Hertz (Hz).
     * @details The frequency at which the driver's moving parts resonate when not in an enclosure. A fundamental parameter for all enclosure calculations.
     * @return double The resonance frequency in Hz.
     */
    double fs() const;

    /** * @brief Returns the mechanical Q-factor (Qms).
     * @details Represents the mechanical damping of the driver's suspension (surround and spider). A fundamental measured parameter.
     * @return double The mechanical Q-factor (dimensionless).
     */
    double qms() const;

    /** * @brief Returns the electrical Q-factor (Qes).
     * @details Represents the electrical damping from the motor system. This value is read from the JSON or calculated if not present.
     * @return double The electrical Q-factor (dimensionless).
     */
    double qes() const;

    /** * @brief Returns the total Q-factor (Qts).
     * @details The combination of mechanical (Qms) and electrical (Qes) damping. Qts is the primary indicator for a driver's suitability for a specific enclosure type (e.g., sealed, ported).
     * @return double The total Q-factor (dimensionless).
     */
    double qts() const;

    /** * @brief Returns the total moving mass (Mms) in kilograms (kg).
     * @details Includes the mass of the cone, voice coil, and the acoustic load of the air in front of and behind the cone. A fundamental parameter.
     * @return double The moving mass in kg.
     */
    double mms() const;

    /** * @brief Returns the diaphragm/cone mass (Mmd) in kilograms (kg).
     * @details The moving mass without the air load.
     * @return double The diaphragm mass in kg.
     */
    double mmd() const;

    /** * @brief Returns the stiffness of the driver suspension (Kms) in Newtons per meter (N/m).
     * @details The inverse of Cms.
     * @return double The suspension stiffness in N/m.
     */
    double stiffness() const;

    /** * @brief Returns the compliance of the driver suspension (Cms) in meters per Newton (m/N).
     * @details Represents the "springiness" of the suspension. Directly related to Fs and Mms.
     * @return double The suspension compliance in m/N.
     */
    double cms() const;

    /** * @brief Returns the equivalent compliance volume (Vas) in cubic meters (m³).
     * @details The volume of air that has the same acoustic compliance as the driver's suspension. A crucial parameter for enclosure volume calculation.
     * @return double The equivalent volume in m³.
     */
    double vas() const;

    /** * @brief Returns the mechanical resistance (Rms) in Ns/m.
     * @details Represents losses in the suspension system.
     * @return double The mechanical resistance in Ns/m.
     */
    double rms() const;

    /** * @brief Returns the effective piston area of the cone (Sd) in square meters (m²).
     * @details A fundamental parameter for calculating Vas and Vd.
     * @return double The effective piston area in m².
     */
    double sd() const;

    /** * @brief Returns the maximum linear excursion (Xmax) in meters (m).
     * @details The maximum distance the cone can travel in one direction while maintaining linear behavior. Crucial for determining low-frequency output limits.
     * @return std::optional<double> The Xmax in meters, or std::nullopt if not specified.
     */
    std::optional<double> xmax() const;

    /** * @brief Returns the mechanical excursion limit (Xlim) in meters (m).
     * @details The absolute maximum distance the cone can travel before physical damage occurs.
     * @return std::optional<double> The Xlim in meters, or std::nullopt if not specified.
     */
    std::optional<double> xlim() const;

    /** * @brief Returns the maximum displacement volume (Vd) in cubic meters (m³).
     * @details The volume of air displaced by the cone at Xmax (Sd * Xmax). A key indicator for bass capability.
     * @return std::optional<double> The displacement volume in m³, or std::nullopt if not specified.
     */
    std::optional<double> vd() const;

    // --- Physical Dimension Accessors ---

    /** * @brief Returns the nominal diameter as a string (e.g., "8in", "20cm").
     * @details The commercial size category of the driver.
     * @return const std::string& The nominal diameter string.
     */
    const std::string& nominalDiameter() const;

    /** * @brief Returns the voice coil diameter in meters (m).
     * @return double The voice coil diameter in meters.
     */
    double vcDiameter() const;

    /** * @brief Returns the voice coil winding height in meters (m).
     * @return double The winding height in meters.
     */
    double windingHeight() const;

    /** * @brief Returns the height of the magnetic air gap in meters (m).
     * @return double The air gap height in meters.
     */
    double airGapHeight() const;

    /** * @brief Returns the effective cone diameter in meters (m).
     * @return double The effective diameter in meters.
     */
    double effectiveDiameter() const;

    /** * @brief Returns the recommended baffle cutout diameter in meters (m).
     * @return double The cutout diameter in meters.
     */
    double baffleCutoutDiameter() const;

    /** * @brief Returns the volume occupied by the driver inside an enclosure in cubic meters (m³).
     * @return double The occupied volume in m³.
     */
    double volumeOccupied() const;

    /** * @brief Returns the net weight of the driver in kilograms (kg).
     * @return double The net weight in kg.
     */
    double netWeight() const;

    /** * @brief Returns the primary material of the cone or diaphragm.
     * @return const std::string& The material name.
     */
    const std::string& material() const;
    //// end public member methods

    //// begin public member methods (internal use only)
public:
    //// end public member methods (internal use only)

    //// begin protected member methods
protected:
    //// end protected member methods

    //// begin protected member methods (internal use only)
protected:
    /**
     * @brief Calculates the electrical Q-factor (Qes).
     * @details Represents the electrical damping from the motor system. The calculation is based on the following formula:
     * \f[ Q_{es} = \frac{2 \pi \cdot F_s \cdot M_{ms} \cdot R_e}{Bl^2} \f]
     * @return The calculated electrical Q-factor (dimensionless).
     */
    double calculateQes() const;

    /**
     * @brief Calculates the total Q-factor (Qts).
     * @details The combination of mechanical (Qms) and electrical (Qes) damping. The calculation is based on the following formula for parallel components:
     * \f[ Q_{ts} = \frac{Q_{ms} \cdot Q_{es}}{Q_{ms} + Q_{es}} \f]
     * @return The calculated total Q-factor (dimensionless).
     */
    double calculateQts() const;

    /**
     * @brief Calculates the compliance of the driver suspension (Cms).
     * @details Represents the "springiness" of the suspension. It's calculated from the resonance frequency and moving mass:
     * \f[ C_{ms} = \frac{1}{(2 \pi \cdot F_s)^2 \cdot M_{ms}} \f]
     * @return The calculated suspension compliance in meters per Newton (m/N).
     */
    double calculateCms() const;

    /**
     * @brief Calculates the stiffness of the driver suspension (Kms).
     * @details The inverse of Cms. The calculation is based on the following formula:
     * \f[ K_{ms} = (2 \pi \cdot F_s)^2 \cdot M_{ms} \f]
     * @return The calculated suspension stiffness in Newtons per meter (N/m).
     */
    double calculateKms() const;

    /**
     * @brief Calculates the equivalent compliance volume (Vas).
     * @details The volume of air that has the same acoustic compliance as the driver's suspension. The formula is:
     * \f[ V_{as} = \rho_0 \cdot c^2 \cdot S_d^2 \cdot C_{ms} \f]
     * where \f$\rho_0\f$ is the density of air and \f$c\f$ is the speed of sound.
     * @return The calculated equivalent volume in cubic meters (m³).
     */
    double calculateVas() const;

    /**
     * @brief Calculates the maximum displacement volume (Vd).
     * @details The volume of air displaced by the cone at Xmax. The formula is:
     * \f[ V_d = S_d \cdot X_{max} \f]
     * @return std::optional<double> The calculated displacement volume in m³, or std::nullopt if Xmax is not available.
     */
    std::optional<double> calculateVd() const;

    /**
     * @brief Calculates the characteristic sensitivity.
     * @details The sensitivity is derived from the efficiency (\f$\eta_0\f$). The formulas are:
     * \f[ \eta_0 = \frac{4 \pi^2 \cdot F_s^3 \cdot V_{as}}{c^3 \cdot Q_{es}} \f]
     * \f[ SPL = 112 + 10 \cdot \log_{10}(\eta_0) \f]
     * @return The calculated sensitivity in dB (1W/1m).
     */
    double calculateSensitivity() const;
    //// end protected member methods (internal use only)

    //// begin private member methods
private:
    //// end private member methods

    //// begin public member
public:
    //// end public member

    //// begin protected member
protected:
    //// end protected member

    //// begin private member
private:
    // Member variables for storing data
    // General Info
    std::string m_uuid;
    std::string m_brand;
    std::string m_manufacturer;
    std::string m_providedby;
    std::string m_comment;
    std::string m_model;
    bool m_indexed;
    std::string m_speaker_type;

    // Electrical Parameters
    double m_impedance;
    double m_sensitivity;
    double m_re;
    double m_le;
    double m_znom;
    double m_pe;
    double m_pmax;
    double m_bl;
    double m_motor_constant;
    double m_flux_density;

    // Thiele-Small Parameters (in SI units)
    double m_fs;
    double m_qms;
    double m_qes;
    double m_qts;
    double m_mms_kg;
    double m_mmd_kg;
    double m_stiffness;
    double m_cms;
    double m_vas_m3;
    double m_rms;
    double m_sd_m2;
    std::optional<double> m_xmax_m;
    std::optional<double> m_xlim_m;
    std::optional<double> m_vd_m3;

    // Physical Dimensions (in SI units)
    std::string m_nominal_diameter;
    double m_vc_diameter_m;
    double m_winding_height_m;
    double m_air_gap_height_m;
    double m_effective_diameter_m;
    double m_baffle_cutout_diameter_m;
    double m_volume_occupied_m3;
    double m_net_weight_kg;
    std::string m_material;
    //// end private member
};
}
