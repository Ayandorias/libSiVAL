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
#include <vector>
//// end system includes

//// begin project specific includes
#include <sival/abstractions/driver.hpp>
#include <sival/abstractions/enclosure.hpp>
#include <sival/abstractions/response.hpp>
#include <sival/core/roleconfig.hpp>
#include <sival/sival.hpp>
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

class AcousticSetup {

    //// begin public member methods
public:
    AcousticSetup(SiVAL::EnclosureType type);
    AcousticSetup(const std::string &json);
    ~AcousticSetup();
    bool addDriver(SiVAL::DriverRole role, const std::string &json, int count);
    bool addResponse(std::unique_ptr<AbstractResponse> response);
    RoleConfig* driverByRole(SiVAL::DriverRole role);
    SiVAL::AbstractEnclosure& enclosure();
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
    std::map<ResponseType, std::unique_ptr<AbstractResponse>> m_responses;
    //// end private member
};
}
