#include "Boid.hpp"

const double PI = 3.141592653589793238463;

Boid::Boid(sf::Vector2f l_pos)
    : m_mass{1}, m_pos{l_pos}, m_velocity{0, 0}, m_acceleration{0, 0}
{
    m_velocity = sf::Vector2f(2 * ( rand() / RAND_MAX ) - 1, 2 * ( rand() / RAND_MAX ) - 1);
    Vec::SetMagnitude(m_velocity, (rand() / (float)RAND_MAX) * constants::k_maxSpeed );
    // Normalise velocity and multiply by speed
    m_colour = {rand() % 256, rand() % 256, rand() % 256};
}

Boid::Boid(unsigned int l_winWidth, unsigned int l_winHeight)
    : m_mass{1}, m_velocity{0, 0}, m_acceleration{0, 0}
{
    m_velocity = {2 * ( rand() / (float)RAND_MAX ) - 1, 2 * ( rand() / (float)RAND_MAX ) - 1};
    Vec::SetMagnitude(m_velocity, (rand() / (float)RAND_MAX) * constants::k_maxSpeed );
    m_pos = {rand() % l_winWidth, rand() % l_winHeight};
    m_colour = {rand() % 256, rand() % 256, rand() % 256};
}

Boid::~Boid()
{

}

void Boid::Flock(const std::vector<Boid*> l_flock)
{
    ApplyForce(CalculateAlignmentForce(l_flock) + CalculateCohesionForce(l_flock) + CalculateSeparationForce(l_flock));
}

void Boid::Update(float l_dt)
{
    m_velocity += m_acceleration;
    m_acceleration = sf::Vector2f(0, 0);
    m_pos += l_dt * m_velocity;
}

sf::Vector2f Boid::CalculateSeekForce(sf::Vector2f l_target, double l_strengthCoeff)
{
    sf::Vector2f force = (l_target - m_pos) * (float)l_strengthCoeff;
    if (Vec::GetMagnitude(force) > (float)constants::k_maxForce)
    {
        Vec::SetMagnitude(force, constants::k_maxForce);
    }
    return force;
}

sf::Vector2f Boid::CalculateAlignmentForce(const std::vector<Boid*> l_flock)
{
    // Alignment
}

sf::Vector2f Boid::CalculateCohesionForce(const std::vector<Boid*> l_flock)
{
    // Cast this to const pointer
    if (l_flock.size() < 2) { return {0, 0}; }
    Boid * const curr = this;
    sf::Vector2f avgPos {0, 0};
    for (const auto &boid : l_flock)
    {
        if (curr == boid) { continue; }
        avgPos += boid->GetPos();
    }
    avgPos /= (float)l_flock.size();
    return CalculateSeekForce(avgPos, constants::k_cohesionCoeff);
}

sf::Vector2f Boid::CalculateSeparationForce(const std::vector<Boid*> l_flock)
{
    // Separation
}

void Boid::ApplyForce(sf::Vector2f l_force)
{
    m_acceleration += l_force / m_mass;
}

sf::Vector2f Boid::GetPos()
{
    return m_pos;
}

double Boid::GetBearing()
{
    if (m_velocity.x == 0.0f)
    {
        if (m_velocity.y == 0.0f)
        {
            return 0;
        }
        return (m_velocity.y > 0) ? 0 : 180;
    }
    if (m_velocity.x > 0)
    {
        return ((std::atan(m_velocity.y / m_velocity.x) / PI) * 180) + 90;
    }
    else
    {
        return ((std::atan(m_velocity.y / m_velocity.x) / PI) * 180) - 90;
    }
}

sf::Color Boid::GetCol()
{
    return m_colour;
}