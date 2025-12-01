#pragma once

#include <string>
#include "sival/libsival.hpp" // For EnclosureType

namespace SiVAL {

/**
 * @class AbstractEnclosure
 * @brief Abstract base class that defines the common interface and base data for enclosure types.
 *
 * @details This class establishes the fundamental functionality common to all
 * enclosure implementations within the library. Its primary responsibility is to
 * manage fundamental properties such as the volume (`m_volume`) and a type
 * identifier (`m_type`).
 *
 * Direct instantiation of this class is not possible as it contains a pure
 * virtual function (`toJson()`). Any derived, concrete enclosure class is

 * required to implement this function.
 *
 * The constructors are `protected` to ensure they can only be called by
 * derived classes.
 */
class LIB_SIVAL_EXPORT AbstractEnclosure
{
public:
    /**
     * @brief Virtual destructor to ensure correct destruction of derived objects.
     */
    virtual ~AbstractEnclosure();

    /**
     * @brief Sets the internal net volume of the enclosure.
     * @param vol The volume in liters.
     */
    void setVolume(double vol);

    /**
     * @brief Pure virtual function for serializing the object's state.
     * @details Derived classes must implement this method to return a complete
     * representation of their state as a JSON string.
     * @return A string representing the object in JSON format.
     */
    virtual std::string toJson() = 0;

    /**
     * @brief Returns the type identifier of this enclosure.
     * @return The `EnclosureType` value set by the derived class's constructor.
     */
    SiVAL::EnclosureType type();

    /**
     * @brief Returns the internal net volume of the enclosure.
     * @return The volume in liters.
     */
    double volume();

protected:
    /**
     * @brief Protected constructor for use by derived classes.
     * @param type The `EnclosureType` identifier for this enclosure.
     */
    explicit AbstractEnclosure(SiVAL::EnclosureType type);

    /**
     * @brief Protected constructor for use by derived classes.
     * @details This constructor is intended for derived classes that perform their
     * initialization from a JSON string. The base class itself does not
     * perform any analysis of the string.
     * @param json The JSON string containing the enclosure data.
     */
    explicit AbstractEnclosure(const std::string& json);

    /// The type identifier, set in the constructor by the derived class.
    SiVAL::EnclosureType m_type;

    /// The internal net volume of the enclosure in liters.
    double m_volume;
};

} // namespace SiVAL
