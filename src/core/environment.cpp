#include "sival/core/environment.hpp"
#include "sival/abstractions/abstractdriverresolver.hpp"

namespace SiVAL {

// --- Konstruktor ---
Environment::Environment(AbstractDriverResolver& resolver)
    : m_driverResolver(resolver),
    m_speedOfSound(kDefaultSpeedOfSound),
    m_densityOfAir(kDefaultDensityOfAir)
{}

// --- Öffentliche Methoden (alphabetisch) ---
double Environment::defaultDensityOfAir() {
    return kDefaultDensityOfAir;
}

double Environment::defaultSpeedOfSound() {
    return kDefaultSpeedOfSound;
}

double Environment::densityOfAir() const {
    return m_densityOfAir;
}

AbstractDriverResolver& Environment::driverResolver() const {
    return m_driverResolver;
}

void Environment::resetDensityOfAir() {
    m_densityOfAir = kDefaultDensityOfAir;
}

void Environment::resetSpeedOfSound() {
    m_speedOfSound = kDefaultSpeedOfSound;
}

void Environment::setDensityOfAir(double density) {
    m_densityOfAir = density;
}

void Environment::setSpeedOfSound(double speed) {
    m_speedOfSound = speed;
}

double Environment::speedOfSound() const {
    return m_speedOfSound;
}

} // namespace SiVAL
