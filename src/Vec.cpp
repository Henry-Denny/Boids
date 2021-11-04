#include "Vec.hpp"

float Vec::GetMagnitude(sf::Vector2f l_vec)
{
    return std::sqrt((l_vec.x * l_vec.x) + (l_vec.y * l_vec.y));
}

void Vec::Normalise(sf::Vector2f &l_vec)
{
    l_vec /= GetMagnitude(l_vec);
}

void Vec::SetMagnitude(sf::Vector2f &l_vec, float l_mag)
{
    Normalise(l_vec);
    l_vec *= l_mag;
}