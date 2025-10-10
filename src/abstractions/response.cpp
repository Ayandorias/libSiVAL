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
#include "sival/abstractions/response.hpp"
//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin extern declaration
//// end extern declaration

//// begin static definitions
//// end static definitions

//// begin static functions
//// end static functions

//// begin public member methods
SiVAL::AbstractResponse::AbstractResponse(ResponseType type)
    : m_type(type) {
}

SiVAL::AbstractResponse::~AbstractResponse() {
}
void SiVAL::AbstractResponse::setSpeaker(std::shared_ptr<const SiVAL::AbstractDriver> speaker) {
    m_speaker = speaker;
}
void SiVAL::AbstractResponse::setEnclosure(std::shared_ptr<const SiVAL::AbstractEnclosure> enclosure) {
    m_enclosure = enclosure;
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
