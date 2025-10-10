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
#include <sival/abstractions/enclosure.hpp>
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
AbstractEnclosure::~AbstractEnclosure() {
}
void AbstractEnclosure::setVolume(double vol) {
    m_volume = vol;
}
SiVAL::EnclosureType AbstractEnclosure::type() {
    return m_type;
}
double AbstractEnclosure::volume() {
    return m_volume;
}
//// end public member methods

//// begin public member methods (internal use only)
//// end public member methods (internal use only)

//// begin protected member methods
AbstractEnclosure::AbstractEnclosure(SiVAL::EnclosureType type)
    : m_type(type) {
}
AbstractEnclosure::AbstractEnclosure(const std::string &json) {

}
//// end protected member methods

//// begin protected member methods (internal use only)
//// end protected member methods (internal use only)

//// begin private member methods
//// end private member methods

} // namespace SiVAL
