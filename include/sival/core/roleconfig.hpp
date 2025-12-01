#pragma once

#include <memory>

// Forward declaration to avoid including the full driver header
namespace SiVAL {
class AbstractDriver;
}

namespace SiVAL {

/**
 * @class RoleConfig
 * @brief Encapsulates a driver model and its quantity.
 *
 * @details This class acts as a simple data container. Its purpose is to define
 * which driver model (`AbstractDriver`) is used and in what quantity (`count`)
 * for a logical position within a system.
 */
class LIB_SIVAL_EXPORT RoleConfig
{
public:
    /**
     * @brief Default constructor.
     */
    RoleConfig() = default;

    /**
     * @brief Constructs a RoleConfig with a specific driver and count.
     * @param d A `shared_ptr` to the driver model.
     * @param c The quantity of identical drivers of this model.
     */
    RoleConfig(std::shared_ptr<AbstractDriver> d, int c = 1)
        : driver(d), count(c)
    {}

    /**
     * @brief A `shared_ptr` that points to the driver model used for this role.
     */
    std::shared_ptr<AbstractDriver> driver = nullptr;

    /**
     * @brief The quantity of identical drivers of this model to be used for the role.
     */
    int count = 1;
};

} // namespace SiVAL
