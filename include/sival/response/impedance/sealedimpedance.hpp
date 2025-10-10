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
#include <sival/enclosure/enclosure.hpp>
#include <sival/speaker/speaker.hpp>
#include <sival/response/impedance.hpp>
//// end project specific includes

//// begin using namespaces
//// end using namespaces

//// begin global definition
//// end global definition

//// begin forward declarations
//// end forward declarations

//// begin extern declaration
//// end extern declaration

namespace SiVAL::Response {

/**
 * @class SealedImpedance
 * @ingroup Response
 * @brief Represents and calculates the electrical impedance of a loudspeaker system.
 *
 * @details
 * ### Fundamental Explanation of the Calculation
 *
 * This class models the electrical behavior of an entire system, which consists of a
 * loudspeaker (`Speaker`) and an enclosure (`Enclosure`). It serves as the central
 * calculator that combines the properties of both components.
 *
 * The fundamental formula for calculating the total impedance \f$ Z_{total} \f$ is:
 *
 * \f[ Z_{total}(f) = Z_{el}(f) + Z_{mot}(f) \f]
 *
 * Here, \f$ Z_{el} \f$ is the purely electrical impedance of the voice coil, which
 * depends directly on the parameters of the `Speaker` object. The component \f$ Z_{mot} \f$
 * is the motional impedance, which represents the mechanical properties of the vibrating
 * system. It results from the complex interaction of the parameters from the
 * `Speaker` object and the physical reaction of the `Enclosure` object.
 *
 * The class internally holds references to the system components and uses their
 * interfaces to perform the detailed calculation in the `Response()` function.
 */
class SealedImpedance : public Impedance
{

    //// begin public member methods
public:
    /**
     * @brief Constructor that initializes the system with a speaker and an enclosure.
     * @param speaker A pointer to a constant Speaker object.
     * @param enclosure A pointer to a constant Enclosure object.
     */
    explicit SealedImpedance(std::shared_ptr<const SiVAL::Speaker::Speaker> speaker, std::shared_ptr<const SiVAL::Enclosure::Enclosure> enclosure);
    /// Destructor
    virtual ~SealedImpedance();
    /**
     * @brief Calculates the magnitude of the system's total impedance at a specific frequency.
     *
     * @param frequency The frequency in Hertz at which the impedance should be calculated.
     *
     * @return double The magnitude (absolute value) of the total impedance \f$ |Z_{total}| \f$ in Ohms.
     *
     * @details
     * ### Detailed Description of the Calculation
     *
     * This function implements the complete physical derivation of the system impedance.
     * The calculation is performed step-by-step by combining the electrical,
     * mechanical, and acoustical domains.
     *
     * **1. Electrical Impedance (\f$ Z_{el} \f$)**
     *
     * The first term is the impedance of the voice coil at rest. Its parameters
     * \f$ R_e \f$ (DC resistance) and \f$ L_e \f$ (inductance) are retrieved from the
     * `m_speaker` object.
     *
     * \f[ Z_{el}(f) = R_e + j \omega L_e \f]
     *
     * **2. Motional Impedance (\f$ Z_{mot} \f$)**
     *
     * The second term describes the back-EMF induced by the diaphragm's motion.
     * The force factor \f$ Bl \f$ is taken from the `m_speaker` object.
     *
     * \f[ Z_{mot}(f) = \frac{(Bl)^2}{Z_{mech\_ges}(f)} \f]
     *
     * **3. Total Mechanical Impedance (\f$ Z_{mech\_ges} \f$)**
     *
     * This is the sum of the mechanical impedances of the driver and the enclosure.
     *
     * \f[ Z_{mech\_ges}(f) = Z_{mech\_treiber}(f) + Z_{mech\_gehäuse}(f) \f]
     *
     * **3.1. Driver's Mechanical Impedance (\f$ Z_{mech\_treiber} \f$)**
     *
     * The parameters \f$ R_{ms} \f$ (mechanical losses), \f$ M_{ms} \f$ (moving mass), and
     * \f$ C_{ms} \f$ (suspension compliance) are provided entirely by the `m_speaker` object.
     *
     * \f[ Z_{mech\_treiber}(f) = R_{ms} + j \left( \omega M_{ms} - \frac{1}{\omega C_{ms}} \right) \f]
     *
     * **3.2. Enclosure's Mechanical Impedance (\f$ Z_{mech\_gehäuse} \f$)**
     *
     * The properties of the enclosure are provided by the `m_enclosure` object, specifically
     * the volume \f$ V_b \f$ and the quality factor \f$ Q_l \f$. From \f$ V_b \f$, the acoustic
     * compliance \f$ C_{ab} \f$ of the enclosed air is calculated.
     *
     * \f[ C_{ab} = \frac{V_b}{\rho_0 c_0^2} \f]
     *
     * To convert this acoustical quantity into the mechanical domain and to account for
     * the losses represented by \f$ Q_l \f$, the diaphragm area \f$ S_d \f$ from the
     * `m_speaker` object is required.
     *
     * **4. Magnitude Calculation**
     *
     * The previously calculated terms are summed to yield the complex total impedance \f$ Z_{total} \f$.
     * Finally, the absolute value of this complex number is taken using `std::abs`
     * and returned as a `double` value.
     */
    double response(double frequency) const;
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
    //// end private member
};
}




