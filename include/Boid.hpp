#ifndef BOID_HPP
#define BOID_HPP

#include <random>
#include <vector>
#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Constants.hpp"
#include "Vec.hpp"
#include "Behaviours.hpp"

class Boid
{
public:
    Boid(sf::Vector2f l_pos);
    Boid(unsigned int l_winWidth, unsigned int l_winHeight);
    ~Boid();


    // Change the acceleration
    void Flock(const std::vector<Boid*> l_flock, sf::Vector2f l_centralisationNode, std::uint8_t behaviourOptions = 0b11111111, bool l_anticlockwiseOrbit = true);
    // Apply the acceleration
    void Update(float l_dt);

    sf::Vector2f CalculateSeekForce(sf::Vector2f l_target, double l_strengthCoeff = 1.0f);
    sf::Vector2f CalculateAlignmentForce(const std::vector<Boid*> l_flock);
    sf::Vector2f CalculateCohesionForce(const std::vector<Boid*> l_flock);
    sf::Vector2f CalculateSeparationForce(const std::vector<Boid*> l_flock);
    sf::Vector2f CalculateOrbitalForce(sf::Vector2f l_center = {0, 0}, bool l_anticlockwise = true);
    sf::Vector2f CalculateResistanceForce();

    void ApplyForce(sf::Vector2f l_force);

    sf::Vector2f GetPos();
    float GetSpeed();
    double GetBearing();
    sf::Color GetCol();

private:
    const float m_mass;

    sf::Vector2f m_pos;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;

    sf::Color m_colour;
};

#endif