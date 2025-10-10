/*
 * libSiVAL
 *
 * Copyright (C) since 2025 Bruno Pierucki
 *
 * Author: Bruno Pierucki <b.pierucki@gmx.de>
 */

//// begin includes
//// end includes

//// begin system includes
//// end system includes

//// begin project specific includes
#include "sival/utils/siconverter.hpp"
//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin extern declaration
//// end extern declaration

namespace SiVAL::Utils {

//// begin static definitions
//// end static definitions

//// begin static functions
double SIConverter::toArea(double value, const std::string& unit) {
    if (unit == "cm2") {
        return value * 1e-4; // 1 cm² = 0.0001 m²
    }
    if (unit == "in2") {
        return value * 0.00064516; // 1 in² = 0.00064516 m²
    }
    if (unit == "ft2") {
        return value * 0.092903; // 1 ft² = 0.092903 m²
    }
    // Default to m2 if unit is "m2" or unknown
    return value;
}

double SIConverter::toMass(double value, const std::string& unit) {
    if (unit == "g") {
        return value * 1e-3; // 1 g = 0.001 kg
    }
    if (unit == "oz") {
        return value * 0.0283495; // 1 oz = 0.0283495 kg
    }
    if (unit == "lb") {
        return value * 0.453592; // 1 lb = 0.453592 kg
    }
    // Default to kg if unit is "kg" or unknown
    return value;
}

double SIConverter::toLength(double value, const std::string& unit) {
    if (unit == "mm") {
        return value * 1e-3; // 1 mm = 0.001 m
    }
    if (unit == "cm") {
        return value * 1e-2; // 1 cm = 0.01 m
    }
    if (unit == "in") {
        return value * 0.0254; // 1 in = 0.0254 m
    }
    if (unit == "ft") {
        return value * 0.3048; // 1 ft = 0.3048 m
    }
    // Default to m if unit is "m" or unknown
    return value;
}

double SIConverter::toVolume(double value, const std::string& unit) {
    if (unit == "L" || unit == "l" || unit == "dm3") {
        return value * 1e-3; // 1 L = 0.001 m³
    }
    if (unit == "cm3") {
        return value * 1e-6; // 1 cm³ = 0.000001 m³
    }
    if (unit == "in3") {
        return value * 1.63871e-5; // 1 in³ = 0.0000163871 m³
    }
    if (unit == "ft3") {
        return value * 0.0283168; // 1 ft³ = 0.0283168 m³
    }
    // Default to m3 if unit is "m3" or unknown
    return value;
}
//// end static functions


//// begin public member methods
//// end public member methods

//// begin public member methods (internal use only)
//// end public member methods (internal use only)

//// begin protected member methods
//// end protected member methods

//// begin protected member methods (internal use only)
//// end protected member methods (internal use only)

//// begin private member methods
//// end private member methods

} // namespace SiVAL::Utils
