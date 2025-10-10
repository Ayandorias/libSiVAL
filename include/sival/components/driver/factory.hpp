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
#include <memory>
//// end system includes

//// begin project specific includes
#include <sival/abstractions/driver.hpp>
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
namespace Driver {
/**
 * @class Factory
 * @brief Serves as a polymorphic constructor for instantiating AbstractDriver
 * derivatives from serialized JSON data.
 *
 * @details The architectural necessity of this class arises from the need
 * to decouple client code (e.g., `AcousticSetup`) from the knowledge of
 * concrete, derived driver classes.
 *
 * This class implements the **Factory Method design pattern**. It encapsulates
 * the logic required to determine and instantiate the correct subtype of
 * `AbstractDriver` from a given data structure. The decision-making process
 * is based on the analysis of a defined field within the JSON data, which
 * identifies the specific class type.
 *
 * By centralizing the creation process, the extensibility of the `Driver`
 * module is ensured according to the **Open/Closed Principle**: new driver
 * types can be added by modifying the factory, without requiring changes
 * to the client code that uses it.
 */
class Factory
{

    //// begin public member methods
public:
    static std::shared_ptr<AbstractDriver> create(SiVAL::DriverRole expectedRole, const std::string& jsonFilePath);
    //// end public member methods

    //// begin public member methods (internal use only)
public:
    //// end public member methods (internal use only)

    //// begin protected member methods
protected:
    Factory() = delete;
    //// end protected member methods

    //// begin protected member methods (internal use only)
protected:
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
    //// end private member
};
}
}
