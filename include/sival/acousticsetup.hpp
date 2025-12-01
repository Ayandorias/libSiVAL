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
#include <nlohmann/json.hpp>
//// end system includes

//// begin project specific includes
#include <sival/abstractions/driver.hpp>
#include <sival/abstractions/enclosure.hpp>
#include <sival/abstractions/response.hpp>
#include <sival/core/environment.hpp>
#include <sival/core/roleconfig.hpp>
#include <sival/libsival.hpp>
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

class LIB_SIVAL_EXPORT AcousticSetup {

    //// begin public member methods
public:
    AcousticSetup(std::shared_ptr<SiVAL::Environment> env, SiVAL::EnclosureType type = SiVAL::EnclosureType::Sealed);
    AcousticSetup(std::shared_ptr<SiVAL::Environment> env, const std::string &json);
    ~AcousticSetup();
    bool addDriver(SiVAL::DriverRole role, const std::string &json, int count);
    bool addResponse(std::unique_ptr<AbstractResponse> response);
    RoleConfig* driverByRole(SiVAL::DriverRole role);
    SiVAL::AbstractEnclosure& enclosure();
    std::shared_ptr<SiVAL::Environment> environment();
    void removeDriver(SiVAL::DriverRole role);
    void removeResponse(SiVAL::ResponseType type);
    AbstractResponse* responseByType(SiVAL::ResponseType type);
    void setDriver(SiVAL::DriverRole role, const std::string &json, int count);
    void setResponse(SiVAL::ResponseType type, std::unique_ptr<AbstractResponse> respopnse);
    std::string toJson();
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
    //// end public member

    //// begin protected member
protected:
    //// end protected member

    //// begin private member
private:
    std::map<DriverRole, std::unique_ptr<RoleConfig>> m_drivers;
    std::unique_ptr<SiVAL::AbstractEnclosure> m_enclosure;
    std::shared_ptr<SiVAL::Environment> m_environment;
    std::map<ResponseType, std::unique_ptr<AbstractResponse>> m_responses;
    nlohmann::json m_json;
    //// end private member
};
}
