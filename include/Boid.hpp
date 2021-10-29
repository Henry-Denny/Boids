#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/System/Vector2.hpp>

class Boid
{
public:
    Boid(sf::Vector2f l_pos);
    ~Boid();

private:
    sf::Vector2f m_pos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
};

#endif