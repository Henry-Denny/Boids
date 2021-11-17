#include "Vec.hpp"

float Vec::GetMagnitude(sf::Vector2f l_vec)
{
    return std::sqrt((l_vec.x * l_vec.x) + (l_vec.y * l_vec.y));
}

void Vec::Normalise(sf::Vector2f &l_vec)
{
    l_vec *= InvSqrt((l_vec.x * l_vec.x) + (l_vec.y * l_vec.y));
}

void Vec::SetMagnitude(sf::Vector2f &l_vec, float l_mag)
{
    Normalise(l_vec);
    l_vec *= l_mag;
}

void Vec::Restrict(sf::Vector2f &l_vec, float l_maxMag)
{
    float magnitude = Vec::GetMagnitude(l_vec);
    if (magnitude > l_maxMag) { Vec::SetMagnitude(l_vec, l_maxMag); }
}

float Vec::Distance(sf::Vector2f A, sf::Vector2f B)
{
    return GetMagnitude(B - A);
}

float Vec::InvSqrt(float n)
{
    const float threehalfs = 1.5F;
    float y = n;
    
    long i = * ( long * ) &y;

    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    
    y = y * ( threehalfs - ( (n * 0.5F) * y * y ) );
    
    return y;
}