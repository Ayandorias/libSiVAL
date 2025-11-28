#pragma once

#include <string>

namespace SiVAL {

/**
 * @class AbstractDriverResolver
 * @brief Defines the polymorphic interface for an external data provider that resolves driver data.
 *
 * @details This abstract class is a key component of the library's dependency injection
 * mechanism. It decouples the core logic from knowledge of the file system or other
 * external data sources by delegating the responsibility of finding data to the
 * client application.
 */
class AbstractDriverResolver
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~AbstractDriverResolver() = default;

    /**
     * @brief Resolves a given identifier to the raw JSON data of the driver.
     *
     * @details This is the callback function to be implemented by the client application.
     *
     * A robust implementation should interpret the `identifier` flexibly.
     * The recommended resolution strategy is to first treat the identifier as a
     * direct file path. If that fails, it should be treated as a logical
     * identifier (e.g., a UUID) and located within an application-specific
     * context (e.g., a driver database directory).
     *
     * @param identifier The identifier to look up (e.g., a file path or a UUID).
     * @return A `std::string` containing the complete JSON data of the driver.
     * @throws An implementation must throw an exception derived from `std::exception`
     * (e.g., `SiVAL::Exception::FileAccessError`) in case of failure (e.g., if the driver
     * cannot be found).
     */
    virtual std::string resolve(const std::string& identifier) = 0;
};

} // namespace SiVAL
