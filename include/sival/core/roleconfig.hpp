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

//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin forward declarations
namespace SiVAL {
class AbstractDriver;
}
//// end forward declarations

//// begin extern declaration
//// end extern declaration

namespace SiVAL {
/**
 * class RoleConfig
 *
 * @brief
 *
 */
class RoleConfig
{

    //// begin public member methods
public:
    /**
     * @brief Default constructor.
     */
    RoleConfig() = default;

    /**
     * @brief Constructs a RoleConfig with a specific driver and count.
     * @param driverPtr Pointer to the driver model.
     * @param driverCount The number of drivers of this model.
     */
    RoleConfig(std::shared_ptr<AbstractDriver> d, int c = 1)
        : driver(d), count(c)
    {}
    //// end public member methods

    //// begin public member methods (internal use only)
public:
    //// end public member methods (internal use only)

    //// begin protected member methods
protected:
    //// end protected member methods

    //// begin protected member methods (internal use only)
protected:
    //// end protected member methods (internal use only)

    //// begin private member methods
private:
    //// end private member methods

    //// begin public member
public:
    /**
     * @brief Pointer to the single driver model used for this role.
     * @note This is a non-owning pointer. The memory is managed by AcousticSetup's
     * driver library.
     */
    std::shared_ptr<AbstractDriver> driver = nullptr;

    /**
     * @brief The quantity of the driver model to be used.
     * @details Defaults to 1, which is the most common use case.
     */
    int count = 1;
    //// end public member

    //// begin protected member
protected:
    //// end protected member

    //// begin private member
private:
    //// end private member
};
}
