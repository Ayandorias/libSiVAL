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
// void AcousticSetup::addResponse(std::unique_ptr<SiVAL::AbstractResponse> response) {
//     // if(response) {
//     //     if(!response->speaker) response->setSpeaker(*m_speaker);
//     //     if(!response->enclosure) response->setEnclosure(*m_enclosure);
//     //     m_responses.push_back(std::move(response));
//     // }
// }
RoleConfig* AcousticSetup::driver(SiVAL::DriverRole role) {
    return nullptr;
}
AbstractEnclosure& AcousticSetup::enclosure() {
    return *m_enclosure;
}
void SiVAL::AcousticSetup::removeDriver(SiVAL::DriverRole role) {
    if(m_drivers.erase(role) == 0) {
        throw SiVAL::Exceptions::OutOfRange("There is driver with the role: " + SiVAL::roleToString(role));
    }
}
// AbstractResponse* SiVAL::AcousticSetup::responseByType(SiVAL::RESPONSE_TYPE type) {
//     // for(const auto& r : m_responses) {
//     //     if(r->type() == type) return r.get();
//     // }
//     return nullptr;
// }

void AcousticSetup::setDriver(SiVAL::DriverRole role, const std::string &json, int count) {
    std::unique_ptr<RoleConfig> rc = std::make_unique<RoleConfig>(SiVAL::Driver::Factory::create(role, json), count);
    m_drivers[role] = std::move(rc);
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
