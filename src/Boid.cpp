#include "Boid.hpp"

Boid::Boid(sf::Vector2f l_pos)
    : m_mass{1}, m_pos{l_pos}, m_velocity{0, 0}, m_acceleration{0, 0}
{
    m_velocity = sf::Vector2f(2 * (rand()/RAND_MAX) - 1, 2 * (rand()/RAND_MAX) - 1);
    // Normalise velocity and multiply by speed
}

Boid::~Boid()
{

}

void Boid::Flock(const std::vector<Boid*> l_flock)
{
    ApplyForce(CalculateAlignmentForce(l_flock) + CalculateCohesionForce(l_flock) + CalculateSeparationForce(l_flock));
}

void Boid::Update()
{
    m_velocity += m_acceleration;
    m_acceleration = sf::Vector2f(0, 0);
}

sf::Vector2f Boid::CalculateAlignmentForce(const std::vector<Boid*> l_flock)
{
    // Alignment
}

sf::Vector2f Boid::CalculateCohesionForce(const std::vector<Boid*> l_flock)
{
    // Cohesion
}

sf::Vector2f Boid::CalculateSeparationForce(const std::vector<Boid*> l_flock)
{
    // Separation
}

void Boid::ApplyForce(sf::Vector2f l_force)
{
    m_acceleration += l_force / m_mass;
}