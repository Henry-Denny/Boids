#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace constants
{
    const unsigned int k_windowSize[] {1200, 1200};

    const double k_alignmentCoeff { 0.05f };
    const double k_cohesionCoeff { 10.0f };
    const double k_avoidanceCoeff { 2000.0f };
    const double k_orbitalCoeff { 20.0f };
    const double k_resistanceCoeff { 20.0f };
    const double k_visionRadius { 40.0f };
    const double k_visionAngle { 30.0f };
    const double k_initialSpeed { 40.0f };
    const double k_maxForce { 2000.0f };
    const double k_maxSpeed { 1000.0f };
};

#endif