#pragma once

#include <memory>
#include "sival/abstractions/enclosure.hpp"
#include "sival/abstractions/driver.hpp"
#include "sival/core/roleconfig.hpp"
#include "sival/libsival.hpp"

namespace SiVAL {

/**
 * @class AbstractResponse
 * @brief Abstract base class that defines an interface for system response calculations.
 *
 * @details This class establishes the fundamental contract for all calculation engines
 * within the library. Its primary responsibility is to manage the context for a
 * calculation by holding references to the required input data—a driver
 * (`AbstractDriver`) and an enclosure (`AbstractEnclosure`).
 *
 * Direct instantiation of this class is not possible. Derived classes must
 * implement the pure virtual `response()` function to provide the specific
 * calculation logic. They have access to the `protected` members of this base
 * class for their calculations.
 */
class LIB_SIVAL_EXPORT AbstractResponse
{
public:
    /**
     * @brief Constructor that initializes the response with its type and an enclosure.
     * @param type The specific type of the response (e.g., `ResponseType::Spl`).
     * @param enclosure A reference to the enclosure object to be used.
     */
    explicit AbstractResponse(ResponseType type, AbstractEnclosure& enclosure);

    /**
     * @brief Virtual destructor to ensure correct destruction of derived objects.
     */
    virtual ~AbstractResponse();

    /**
     * @brief Sets the driver to be simulated using a RoleConfig object.
     * @param config The `RoleConfig` object defining the driver and its count.
     */
    void setDriver(RoleConfig config);

    /**
     * @brief Overloaded function to directly set the driver and its count.
     * @param driver A `shared_ptr` to the const driver object.
     * @param count The quantity of identical drivers for the simulation.
     */
    void setDriver(std::shared_ptr<const SiVAL::AbstractDriver> driver, int count);

    /**
     * @brief Assigns a new enclosure to the response calculation.
     * @param enclosure A reference to the new enclosure object.
     */
    void setEnclosure(SiVAL::AbstractEnclosure& enclosure);

    /**
     * @brief Returns the type of this response.
     * @return The `ResponseType` value set in the constructor.
     */
    ResponseType type();

    /**
     * @brief Pure virtual calculation function that must be implemented by derived classes.
     * @details This is the core method of every response calculation. It performs the
     * specific calculation for the given frequency.
     * @param frequency The frequency in Hertz for which the value should be calculated.
     * @return The calculated result as a `double`.
     */
    virtual double response(double frequency) = 0;

protected:
    /// A `shared_ptr` to the driver used for the calculation.
    std::shared_ptr<const SiVAL::AbstractDriver> m_driver;

    /// A reference to the enclosure.
    SiVAL::AbstractEnclosure& m_enclosure;

    /// The type of this response, set in the constructor.
    ResponseType m_type;

    /// The number of drivers to be considered in the simulation.
    int m_count;
};

}
