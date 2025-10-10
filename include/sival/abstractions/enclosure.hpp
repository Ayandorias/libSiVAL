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
//// end system includes

//// begin project specific includes
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
 * class AbstractEnclosure
 *
 * @brief
 *
 */
class AbstractEnclosure
{

    //// begin public member methods
public:
    virtual ~AbstractEnclosure();
    void setVolume(double vol);
    virtual std::string toJson() = 0;
    SiVAL::EnclosureType type();
    double volume();
    //// end public member methods

    //// begin public member methods (internal use only)
public:
    //// end public member methods (internal use only)

    //// begin protected member methods
protected:
    explicit AbstractEnclosure(SiVAL::EnclosureType type);
    explicit AbstractEnclosure(const std::string &json);
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
    SiVAL::EnclosureType m_type;
    double m_volume;
    //// end protected member

    //// begin private member
private:
    //// end private member
};
}
