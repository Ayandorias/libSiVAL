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
#include "sival/response/sealedimpedance.hpp"
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
SiVAL::Response::SealedImpedance::SealedImpedance(std::shared_ptr<const SiVAL::Speaker::Speaker> speaker, std::shared_ptr<const SiVAL::Enclosure::Enclosure> enclosure)
    :Impedance() {
    m_speaker = speaker;
    m_enclosure = enclosure;
}

SiVAL::Response::SealedImpedance::~SealedImpedance() {
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
