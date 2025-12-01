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
//// end system includes

//// begin project specific includes

//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin forward declarations
//// end forward declarations

//// begin extern declaration
//// end extern declaration

namespace SiVAL::Utils {
/**
 * @class SIConverter
 * @brief A utility class providing static methods for unit conversions.
 *
 * This class serves as a foundational pillar for data integrity within the system.
 * It offers a centralized and authoritative collection of methods for converting
 * various physical quantities from common units found in datasheets (both metric
 * and imperial) into their standard SI (International System of Units) base units.
 * By encapsulating the conversion logic, it ensures consistency and accuracy across
 * all calculations.
 *
 * All methods are static, meaning they belong to the class itself rather than an
 * instance. This design choice reflects their nature as pure, stateless functions,
 * eliminating the need to create an object to perform conversions.
 */
class LIB_SIVAL_EXPORT SIConverter {
public:
    /**
     * @brief Converts an area value from a specified unit to square meters (m²)   ($$\text{m}^2$$).
     * @details This function takes a numerical area value and a string representing its unit,
     * and returns the equivalent area in the SI base unit of square meters. It is
     * essential for standardizing diaphragm area (Sd) measurements.
     *
     * | Input Unit (`unit`) | Unit Meaning         | Output SI Unit        |
     * | :------------------ | :------------------- | :-------------------- |
     * | `m2`                | Square Meter         | Square Meter (m²)     |
     * | `cm2`               | Square Centimeter    | Square Meter (m²)     |
     * | `in2`               | Square Inch          | Square Meter (m²)     |
     * | `ft2`               | Square Foot          | Square Meter (m²)     |
     *
     * @param value The numerical value of the area.
     * @param unit The unit of the area as a string.
     * @return The area converted to square meters.
     */
    static double toArea(double value, const std::string& unit);

    /**
     * @brief Converts a mass value from a specified unit to kilograms (kg).
     * @details This function processes a mass value, standardizing it to the SI base unit of kilograms.
     * It is crucial for handling moving mass parameters like Mms and Mmd, as well as the
     * net weight of the driver.
     *
     * | Input Unit (`unit`) | Unit Meaning         | Output SI Unit        |
     * | :------------------ | :------------------- | :-------------------- |
     * | `kg`                | Kilogram             | Kilogram (kg)         |
     * | `g`                 | Gram                 | Kilogram (kg)         |
     * | `oz`                | Ounce                | Kilogram (kg)         |
     * | `lb`                | Pound                | Kilogram (kg)         |
     *
     * @param value The numerical value of the mass.
     * @param unit The unit of the mass as a string.
     * @return The mass converted to kilograms.
     */
    static double toMass(double value, const std::string& unit);

    /**
     * @brief Converts a length value from a specified unit to meters (m).
     * @details This function translates various common length units into the SI base unit of meters.
     * This is fundamental for all dimensional parameters, such as diameters, heights,
     * and excursion limits (Xmax).
     *
     * | Input Unit (`unit`) | Unit Meaning         | Output SI Unit        |
     * | :------------------ | :------------------- | :-------------------- |
     * | `m`                 | Meter                | Meter (m)             |
     * | `cm`                | Centimeter           | Meter (m)             |
     * | `mm`                | Millimeter           | Meter (m)             |
     * | `in`                | Inch                 | Meter (m)             |
     * | `ft`                | Foot                 | Meter (m)             |
     *
     * @param value The numerical value of the length.
     * @param unit The unit of the length as a string.
     * @return The length converted to meters.
     */
    static double toLength(double value, const std::string& unit);

    /**
     * @brief Converts a volume value from a specified unit to cubic meters (m³).
     * @details This function normalizes various volume units to the SI base unit of cubic meters.
     * It is essential for parameters like equivalent compliance volume (Vas) and
     * displacement volume (Vd).
     *
     * | Input Unit (`unit`) | Unit Meaning         | Output SI Unit        |
     * | :------------------ | :------------------- | :-------------------- |
     * | `m3`                | Cubic Meter          | Cubic Meter (m³)      |
     * | `dm3`               | Cubic Decimeter      | Cubic Meter (m³)      |
     * | `L` / `l`           | Liter                | Cubic Meter (m³)      |
     * | `cm3`               | Cubic Centimeter     | Cubic Meter (m³)      |
     * | `in3`               | Cubic Inch           | Cubic Meter (m³)      |
     * | `ft3`               | Cubic Foot           | Cubic Meter (m³)      |
     *
     * @param value The numerical value of the volume.
     * @param unit The unit of the volume as a string.
     * @return The volume converted to cubic meters.
     */
    static double toVolume(double value, const std::string& unit);
};
}
