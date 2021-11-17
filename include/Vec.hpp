#ifndef VEC_HPP
#define VEC_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace Vec
{
    float GetMagnitude(sf::Vector2f l_vec);
    void Normalise(sf::Vector2f &l_vec);
    void SetMagnitude(sf::Vector2f &l_vec, float l_maxMag);
    void Restrict(sf::Vector2f &l_vec, float l_mag);
    float Distance(sf::Vector2f A, sf::Vector2f B);
    float InvSqrt(float n);
};

#endif