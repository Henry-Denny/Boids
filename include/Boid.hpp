#ifndef BOID_HPP
#define BOID_HPP

#include <random>
#include <vector>

#include <SFML/System/Vector2.hpp>

class Boid
{
public:
    Boid(sf::Vector2f l_pos);
    ~Boid();


    // Change the acceleration
    void Flock(const std::vector<Boid*> l_flock);
    // Apply the acceleration
    void Update();

    sf::Vector2f CalculateSeekForce(sf::Vector2f l_target);
    sf::Vector2f CalculateAlignmentForce(const std::vector<Boid*> l_flock);
    sf::Vector2f CalculateCohesionForce(const std::vector<Boid*> l_flock);
    sf::Vector2f CalculateSeparationForce(const std::vector<Boid*> l_flock);

    void ApplyForce(sf::Vector2f l_force);

    sf::Vector2f GetPos();
    double GetBearing();

private:
    const float m_mass;

    sf::Vector2f m_pos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
};

#endif