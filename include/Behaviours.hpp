#ifndef BEHAVIOURS_HPP
#define BEHAVIOURS_HPP

enum class Behaviour
{
    Alignment = 1 << 0,
    Cohesion = 1 << 1,
    Separation = 1 << 2,
    Centralisation = 1 << 3,
    Orbit = 1 << 4,
    Resistance = 1 << 5
};

#endif