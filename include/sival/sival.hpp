#pragma once


#include <map>
#include <numbers>
#include <string>

/** @mainpage Introduction to the libSiVAL Framework
 *
 * # Purpose and Function
 *
 * The **libSiVAL** library presents itself as a specialized tool for the **systematic planning** and **technical verification** of loudspeaker enclosures and their drivers. Its necessity is grounded in the complexity with which electro-mechanical forces and acoustic principles interact in the low-frequency domain. This system was established to replace the traditional method of trial and error with a **reliable, digital foundation**. It serves as an auditable basis for all decisions concerning the acoustic design and the adherence to the mechanical **safety limits** of the loudspeaker.
 *
 * ## 1. Predictive Modeling and Design Validation
 *
 * The library functions as a **virtual acoustic laboratory**. It accepts the **technical specifications** of a driver (as provided by the manufacturer) as well as the dimensions of the planned enclosure as input data. Based on this, it conducts a **comprehensive simulation** of the coupled electro-mechanical-acoustic system.
 *
 * The main function is the **prediction of performance prior to physical construction**: The library forecasts the behavior of the loudspeaker in its specific box. This allows designers to optimize the optimal cabinet volume, the tuning of bass reflex ports, and the overall tonal balance completely within the software environment. Crucially, it simultaneously **validates** whether the planned parameters are physically plausible.
 *
 * ## 2. Calculation of Verifiable Performance Metrics
 *
 * libSiVAL encapsulates complicated physics to deliver **objective, easily accessible metrics** that would otherwise only be obtainable with expensive equipment:
 * **AbstractSPL Response and Volume:** It calculates exactly how the **Sound Pressure Level (SPL)** is distributed across the critical low-frequency spectrum. This forms the basis for determining the **sound characteristics** (timbre) and the maximum volume of the system.
 * **Electrical and Mechanical Safety:** It provides the **electrical impedance** (important for amplifier matching and crossover development) and—most critically—the data for **maximum cone excursion**. This mechanical metric serves as a **safety indicator** that guarantees the driver will not be mechanically destroyed under high-power demands.
 */


/**
 * @namespace SiVAL
 * @brief **Simulation, Visualisation and Analysis Software for Loudspeaker (SiVAL)**
 *
 * The primary, overarching namespace for the entire library. \c SiVAL encompasses
 * all sub-systems and utilities dedicated to the **simulation, analysis, and validation**
 * of electro-acoustic transducers and enclosure designs.
 *
 * This namespace serves as the architectural root, ensuring all components are
 * distinct from external dependencies and logically grouped under the library's
 * principal designation.
 */
namespace SiVAL {

/**
 * @namespace SiVAL::AbstractEnclosure
 * @brief **Acoustic AbstractEnclosure Modeling**
 *
 * This namespace is dedicated to the **mathematical and physical modeling** of
 * loudspeaker enclosures. It contains classes that abstract the geometry,
 * acoustic properties, and simulation behavior of various cabinet types.
 *
 * Currently, it includes specific implementations for:
 * - **Sealed Boxes:** Representing closed-box acoustic suspension systems.
 * - **Vented Boxes (Bass-Reflex):** Modeling enclosures with a port or vent.
 *
 * The components within \c AbstractEnclosure manage volume, tuning frequency, damping,
 * and impedance characteristics derived from the enclosure's design.
 */
namespace Enclosure{}
/**
 * @namespace SiVAL::AbstractDriver
 * @brief **Loudspeaker Transducer Management**
 *
 * The \c AbstractDriver namespace is responsible for encapsulating the parameters and
 * dynamic behavior of the **actual electro-acoustic driver** (the loudspeaker unit itself).
 *
 * It houses classes that manage fundamental parameters such as:
 * - **Thiele-Small Parameters (T/S):** Key parameters defining low-frequency performance.
 * - Electrical, mechanical, and thermal limits.
 * - Cone geometry and material properties.
 *
 * This namespace forms the crucial link between raw driver specifications and the
 * system-level simulations conducted by other parts of the library.
 */
namespace Driver{}
/**
 * @namespace SiVAL::Utils
 * @brief **General Utility Functions and Helpers**
 *
 * This namespace provides a collection of small, non-domain-specific classes and
 * functions used to support the primary functionality of the \c SiVAL library.
 *
 * Key components include:
 * - **Unit Conversion:** Classes like \c SIConverter for standardizing physical units.
 * - **Mathematical Operations:** Helper functions for common numerical tasks.
 * - **Error Handling:** Custom exception classes or logging utilities.
 *
 * Components in \c Utils are designed for reusability and operational support
 * across the entire codebase.
 */
namespace Utils{}


/**
 * @defgroup Response Acoustic System Responses
 * @brief This namespace contains all classes and methods dedicated to calculating and managing the output data.
 *
 * [HIER STEHT DIE AUSFÜHRLICHE, NICHT-REDUNDANTE DOKUMENTATION]
 */

/**
 * @namespace SiVAL::Response
 * @ingroup Response
 * @brief This namespace contains all classes and methods dedicated to **calculating and managing the output data**
 * (i.e., the "responses") of a defined loudspeaker system (\c AcousticSetup).
 *
 * The \c Responses namespace is fundamentally focused on **System Analysis**. Its purpose is to quantify
 * the performance of the integrated driver and enclosure setup across various domains.
 *
 * ## Primary Function
 *
 * Classes within this namespace abstract complex acoustic and electrical formulas (like the electrical impedance
 * or the acoustic transfer function) into reusable objects. These objects serve as computational engines
 * that require input from the \c AbstractDriver and \c AbstractEnclosure components to generate frequency-dependent data.
 *
 * **Key Output Metrics Managed Here:**
 * - **AbstractSPL Response:** The acoustic output magnitude and phase.
 * - **AbstractImpedance Response:** The electrical load presented to the amplifier.
 * - **Group Delay:** The measure of phase linearity and impulse response quality.
 *
 * By grouping these functions here, the library separates the **data sources** (\c AbstractDriver, \c AbstractEnclosure)
 * from the **analytical tools** (\c Responses).
 *
 * @see AbstractDriver
 * @see AbstractEnclosure
 */
namespace Response{}


/**
     * @brief The mathematical constant Pi.
     * @note For C++20 and later, using std::numbers::pi from the <numbers> header is preferred.
     */
inline constexpr double PI = std::numbers::pi;

/**
     * @brief Standard density of air (rho_0) at 20°C at sea level.
     * @unit kg/m³
     */
inline constexpr double RHO0 = 1.204;

/**
     * @brief Standard speed of sound (c) in dry air at 20°C.
     * @unit m/s
     */
inline constexpr double C_SOUND = 343.0;


enum class EnclosureType {
    Sealed = 0,
    Vented
};

enum class ErrorCode {
    OutOfRange
};

enum class ResponseType {
    Spl = 0,
    Impedance
};


/**
 * @enum DriverRole
 * @brief Defines the specific function or role of a driver within an
 * acoustic setup.
 */
enum class DriverRole {
    SUBWOOFER,
    WOOFER,
    WOOFER_2,
    MIDRANGE,
    TWEETER,
    FULLRANGE
};

/**
 * @brief Converts a DriverRole value to its corresponding string representation.
 */
inline std::string roleToString(DriverRole role) {
    static const std::map<DriverRole, std::string> roleMap = {
        {DriverRole::SUBWOOFER, "SubWoofer"},
        {DriverRole::WOOFER,    "Woofer"},
        {DriverRole::WOOFER_2,  "Woofer"},
        {DriverRole::MIDRANGE,  "Midrange"},
        {DriverRole::TWEETER,   "Tweeter"},
        {DriverRole::FULLRANGE, "Fullrange"}
    };

    auto it = roleMap.find(role);
    if (it != roleMap.end()) {
        return it->second;
    }
    return "unknown";
}

inline std::string typeToString(ResponseType type) {
    static const std::map<ResponseType, std::string> typeMap = {
        {ResponseType::Spl, "Spl"}
    };

    auto it = typeMap.find(type);
    if (it != typeMap.end()) {
        return it->second;
    }
    return "unknown";
}
}
