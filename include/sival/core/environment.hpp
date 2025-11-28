#pragma once

namespace SiVAL {
class AbstractDriverResolver;
}

namespace SiVAL {

/**
 * @class Environment
 * @brief Provides the execution context for library operations.
 * @details Encapsulates application-specific configurations and dependencies, such
 * as implementations of resolver interfaces. A configured object of this class
 * is passed to library functions that need to access external resources.
 */
class Environment
{
public:
    // --- Constructor ---
    /**
     * @brief Initializes the context with a resolver implementation.
     * @param resolver Reference to a concrete `AbstractDriverResolver` object.
     */
    explicit Environment(AbstractDriverResolver& resolver);

    // --- Public Methods (alphabetical) ---
    /**
     * @brief Returns the default density of air.
     * @return Value in [kg/m³].
     */
    static double defaultDensityOfAir();

    /**
     * @brief Returns the default speed of sound.
     * @return Value in [m/s].
     */
    static double defaultSpeedOfSound();

    /**
     * @brief Returns the configured density of air.
     * @return Value in [kg/m³].
     */
    double densityOfAir() const;

    /**
     * @brief Returns the configured driver resolver.
     * @return Reference to the `AbstractDriverResolver` object.
     */
    AbstractDriverResolver& driverResolver() const;

    /**
     * @brief Resets the density of air to its default value.
     */
    void resetDensityOfAir();

    /**
     * @brief Resets the speed of sound to its default value.
     */
    void resetSpeedOfSound();

    /**
     * @brief Sets the density of air.
     * @param density Value in [kg/m³].
     */
    void setDensityOfAir(double density);

    /**
     * @brief Sets the speed of sound.
     * @param speed Value in [m/s].
     */
    void setSpeedOfSound(double speed);

    /**
     * @brief Returns the configured speed of sound.
     * @return Value in [m/s].
     */
    double speedOfSound() const;

private:
    static constexpr double kDefaultSpeedOfSound = 343.0;
    static constexpr double kDefaultDensityOfAir = 1.204;

    AbstractDriverResolver& m_driverResolver;
    double m_speedOfSound;
    double m_densityOfAir;
};

} // namespace SiVAL
