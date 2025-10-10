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
#include <memory>
//// end system includes

//// begin project specific includes
#include <sival/abstractions/enclosure.hpp>
#include <sival/abstractions/driver.hpp>
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
/**
 * class Response
 *
 * @brief
 *
 */
class AbstractResponse
{

    //// begin public member methods
public:
    /// Constructor
    explicit AbstractResponse(ResponseType type);
    /// Destructor
    virtual ~AbstractResponse();

    /**
     * @brief Sets or updates the AbstractDriver component of the system.
     * @param speaker A pointer to a constant AbstractDriver object.
     */
    void setSpeaker(std::shared_ptr<const SiVAL::AbstractDriver> speaker);

    /**
     * @brief Sets or updates the AbstractEnclosure component of the system.
     * @param enclosure A pointer to a constant AbstractEnclosure object.
     */
    void setEnclosure(std::shared_ptr<const SiVAL::AbstractEnclosure> enclosure);
    ResponseType type();
    //// end public member methods

    //// begin public member methods (internal use only)
public:
    //// end public member methods (internal use only)

    //// begin protected member methods
protected:
    std::shared_ptr<const SiVAL::AbstractDriver> m_speaker;
    std::shared_ptr<const SiVAL::AbstractEnclosure> m_enclosure;
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
    ResponseType m_type;
    //// end protected member

    //// begin private member
private:
    //// end private member
};
}
