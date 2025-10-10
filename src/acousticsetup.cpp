/*
 * libSiVAL
 *
 * Copyright (C) since 2025 Bruno Pierucki
 *
 * Author: Bruno Pierucki <b.pierucki@gmx.de>
 */

//// begin includes
//// end includes

//// begin system includes
//// end system includes

//// begin project specific includes
#include "sival/acousticsetup.hpp"
#include <sival/core/exceptions.hpp>
#include <sival/components/enclosure/factory.hpp>
#include <sival/components/driver/factory.hpp>
//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin extern declaration
//// end extern declaration

//// begin static definitions
//// end static definitions

namespace SiVAL {
//// begin static functions
//// end static functions

//// begin public member methods
AcousticSetup::AcousticSetup(EnclosureType type) {

    m_enclosure = SiVAL::Enclosure::Factory::create(type);
}
AcousticSetup::AcousticSetup(const std::string &json) {

}
AcousticSetup::~AcousticSetup() {
}
bool AcousticSetup::addDriver(SiVAL::DriverRole role, const std::string &json, int count) {
    std::unique_ptr<RoleConfig> rc = std::make_unique<RoleConfig>(SiVAL::Driver::Factory::create(role, json), count);
    std::pair result = m_drivers.emplace(role, std::move(rc));
    return result.second;
}
bool AcousticSetup::addResponse(std::unique_ptr<SiVAL::AbstractResponse> response) {
    std::pair result = m_responses.emplace(response->type(), std::move(response));
    return result.second;
}
RoleConfig* AcousticSetup::driverByRole(SiVAL::DriverRole role) {
    auto it = m_drivers.find(role);

    if (it != m_drivers.end()) {
        // .get() on the unique_ptr returns the raw pointer
        return it->second.get();
    }

    return nullptr; // Not found
}
AbstractEnclosure& AcousticSetup::enclosure() {
    return *m_enclosure;
}
void SiVAL::AcousticSetup::removeDriver(SiVAL::DriverRole role) {
    if(m_drivers.erase(role) == 0) {
        throw SiVAL::Exceptions::OutOfRange("There is no driver with the role: " + SiVAL::roleToString(role));
    }
}
void SiVAL::AcousticSetup::removeResponse(SiVAL::ResponseType type) {
    if(m_responses.erase(type) == 0) {
        throw SiVAL::Exceptions::OutOfRange("There is no response with type: " + SiVAL::typeToString(type));
    }
}
AbstractResponse* SiVAL::AcousticSetup::responseByType(SiVAL::ResponseType type) {
    auto it = m_responses.find(type);

    if (it != m_responses.end()) {
        // .get() on the unique_ptr returns the raw pointer
        return it->second.get();
    }

    return nullptr; // Not found
}

void AcousticSetup::setDriver(SiVAL::DriverRole role, const std::string &json, int count) {
    std::unique_ptr<RoleConfig> rc = std::make_unique<RoleConfig>(SiVAL::Driver::Factory::create(role, json), count);
    m_drivers[role] = std::move(rc);
}
void AcousticSetup::setResponse(SiVAL::ResponseType type, std::unique_ptr<AbstractResponse> response) {
    m_responses[type] = std::move(response);
}
std::string AcousticSetup::toJson() {
    return std::string();
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
} // namespace SiVAL
