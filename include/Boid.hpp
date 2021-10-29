#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/System/Vector2.hpp>

class Boid
{
public:
    Boid();
    ~Boid();

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
};

#endif