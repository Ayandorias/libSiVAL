/*
 * libSiVAL
 *
 * Copyright (C) since 2025 Bruno Pierucki
 *
 * Author: Bruno Pierucki <b.pierucki@gmx.de>
 */

//// begin includes
#include <fstream>
#include <nlohmann/json.hpp>
//// end includes

//// begin system includes
#include <sival/libsival.hpp>
//// end system includes

//// begin project specific includes
#include <sival/core/exceptions.hpp>
#include "sival/components/driver/factory.hpp"
//// end project specific includes

//// begin using namespaces
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
namespace Driver {
//// begin public member methods
std::shared_ptr<AbstractDriver> Factory::create(DriverRole expectedRole, const std::string& jsonFilePath) {
    // // --- Step 1: Open and parse the JSON file once ---
    // std::ifstream file(jsonFilePath);
    // if (!file.is_open()) {
    //     throw FileAccessException("DriverFactory cannot open file: " + jsonFilePath);
    // }

    // nlohmann::json data;
    // try {
    //     file >> data;
    // } catch (const nlohmann::json::parse_error& e) {
    //     throw DriverCreationException("DriverFactory failed to parse JSON: " + std::string(e.what()));
    // }

    // // --- Step 2: Extract the actual type from the JSON data ---
    // const std::string actualType = data.at("general_info").value("speaker_type", "unknown");

    // // --- Step 3: Validate if the actual type matches the expected role ---
    // const std::string expectedTypeString = roleToString(expectedRole);
    // if (actualType != expectedTypeString) {
    //     throw InvalidDriverRoleException(expectedTypeString, actualType);
    // }

    // --- Step 4: Create the appropriate driver instance ---
    // The 'data' object is moved into the constructor.

    // if (actualType == "Woofer") {
    //     return std::make_unique<Driver::Woofer>(std::move(data));
    // }

    // if (actualType == "SubWoofer") {
    //     return std::make_unique<Driver::Subwoofer>(std::move(data));
    // }

    // Extend this list as you implement more driver types
    /*
    if (actualType == "Midrange") {
        return std::make_unique<Driver::Midrange>(std::move(data));
    }

    if (actualType == "Tweeter") {
        return std::make_unique<Driver::Tweeter>(std::move(data));
    }

    if (actualType == "Fullrange") {
        return std::make_unique<Driver::Fullrange>(std::move(data));
    }
    */

    // This case is reached if the type is valid but not yet implemented in the factory
    // throw DriverCreationException("Driver type '" + actualType + "' is not supported by the factory yet.");

    return nullptr;
}

//// end public member methods

//// begin public member methods (internal use only)
//// end public member methods (internal use only)

//// begin protected member methods
//// end protected member methods

//// begin protected member methods (internal use only)
//// end protected member methods (internal use only)

//// begin private member methods
//// end private member methods
}
}
