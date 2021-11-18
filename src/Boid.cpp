#include "Boid.hpp"

const double PI = 3.141592653589793238463;

Boid::Boid(sf::Vector2f l_pos)
    : m_mass{1}, m_pos{l_pos}, m_velocity{0, 0}, m_acceleration{0, 0}
{
    m_velocity = sf::Vector2f(2 * ( rand() / RAND_MAX ) - 1, 2 * ( rand() / RAND_MAX ) - 1);
    Vec::SetMagnitude(m_velocity, (rand() / (float)RAND_MAX) * constants::k_maxSpeed );
    // Normalise velocity and multiply by speed
    m_colour = {sf::Uint8(rand() % 256), sf::Uint8(rand() % 256), sf::Uint8(rand() % 256)};
}

Boid::Boid(unsigned int l_winWidth, unsigned int l_winHeight)
    : m_mass{1}, m_velocity{0, 0}, m_acceleration{0, 0}
{
    m_velocity = {2 * ( rand() / (float)RAND_MAX ) - 1, 2 * ( rand() / (float)RAND_MAX ) - 1};
    Vec::SetMagnitude(m_velocity, (rand() / (float)RAND_MAX) * constants::k_maxSpeed );
    m_pos = {float(rand() % l_winWidth), float(rand() % l_winHeight)};
    m_colour = {sf::Uint8(rand() % 256), sf::Uint8(rand() % 256), sf::Uint8(rand() % 256)};
}

Boid::~Boid()
{

}

void Boid::Flock(const std::vector<Boid*> l_flock, sf::Vector2f l_centralisationNode, std::uint8_t behaviourOptions, bool l_anticlockwiseOrbit)
{
    sf::Vector2f force {0, 0};
    if (behaviourOptions & (std::uint8_t)Behaviour::Alignment)
    {
        force += CalculateAlignmentForce(l_flock);
    }
    if (behaviourOptions & (std::uint8_t)Behaviour::Cohesion)
    {
        force += CalculateCohesionForce(l_flock);
    }
    if (behaviourOptions & (std::uint8_t)Behaviour::Separation)
    {
        force += CalculateSeparationForce(l_flock);
    }
    if (behaviourOptions & (std::uint8_t)Behaviour::Centralisation)
    {
        force += CalculateSeekForce(l_centralisationNode, 15);
    }
    if (behaviourOptions & (std::uint8_t)Behaviour::Orbit)
    {
        force += CalculateOrbitalForce(l_flock, l_anticlockwiseOrbit);
    }
    if (behaviourOptions & (std::uint8_t)Behaviour::Resistance)
    {
        force += CalculateResistanceForce();
    }
    ApplyForce(force);
}

void Boid::Update(float l_dt)
{
    m_velocity += l_dt * m_acceleration;
    Vec::Restrict(m_velocity, constants::k_maxSpeed);
    m_acceleration = sf::Vector2f(0, 0);
    Move(l_dt * m_velocity);
}

sf::Vector2f Boid::CalculateSeekForce(sf::Vector2f l_target, double l_strengthCoeff)
{
    sf::Vector2f force = (l_target - m_pos) * (float)l_strengthCoeff;
    Vec::Restrict(force, (float)constants::k_maxForce);
    return force;
}

sf::Vector2f Boid::CalculateAlignmentForce(const std::vector<Boid*> l_flock)
{
    // Alignment
    if (l_flock.size() < 2) { return {0, 0}; }
    Boid * const curr = this;
    sf::Vector2f avgVel {0, 0};
    bool foundBoid = false;
    for (const auto &boid : l_flock)
    {
        if (curr == boid) { continue; }
        if (Vec::Distance(m_pos, boid->GetPos()) > constants::k_visionRadius) { continue; }
        if (std::abs(GetBearing() - boid->GetBearing()) > constants::k_visionAngle) { continue; }
        foundBoid = true;
        avgVel += boid->GetPos();
    }
    if (!foundBoid) { return {0, 0}; }
    avgVel /= (float)l_flock.size();

    sf::Vector2f force = (avgVel - m_velocity) * (float)constants::k_alignmentCoeff;
    Vec::Restrict(force, (float)constants::k_maxForce);
    return force;
}

sf::Vector2f Boid::CalculateCohesionForce(const std::vector<Boid*> l_flock)
{
    // Cohesion
    if (l_flock.size() < 2) { return {0, 0}; }
    Boid * const curr = this;
    sf::Vector2f avgPos {0, 0};
    bool foundBoid = false;
    for (const auto &boid : l_flock)
    {
        if (curr == boid) { continue; }
        if (Vec::Distance(m_pos, boid->GetPos()) > constants::k_visionRadius) { continue; }
        if (std::abs(GetBearing() - boid->GetBearing()) > constants::k_visionAngle) { continue; }
        foundBoid = true;
        avgPos += boid->GetPos();
    }
    if (!foundBoid) { return {0, 0}; }
    avgPos /= (float)l_flock.size();
    return CalculateSeekForce(avgPos, constants::k_cohesionCoeff);
}

sf::Vector2f Boid::CalculateSeparationForce(const std::vector<Boid*> l_flock)
{
    // Separation
    if (l_flock.size() < 2) { return {0, 0}; }
    Boid * const curr = this;
    sf::Vector2f force {0, 0};
    for (const auto &boid : l_flock)
    {
        if (curr == boid) { continue; }
        sf::Vector2f separationForce = m_pos - boid->GetPos();
        float magnitude = Vec::GetMagnitude(separationForce);
        if (Vec::Distance(m_pos, boid->GetPos()) > constants::k_visionRadius) { continue; }
        Vec::SetMagnitude(separationForce, (float)constants::k_avoidanceCoeff / magnitude);
        force += separationForce;
    }
    return force;
}

sf::Vector2f Boid::CalculateOrbitalForce(const std::vector<Boid*> l_flock, bool l_anticlockwise)
{
    if (l_flock.size() < 2) { return {0, 0}; }
    Boid * const curr = this;
    sf::Vector2f avgPos {0, 0};
    for (const auto &boid : l_flock)
    {
        if (curr == boid) { continue; }
        avgPos += boid->GetPos();
    }
    avgPos /= (float)l_flock.size();
    sf::Vector2f normal = avgPos - m_pos;
    sf::Vector2f tangent = sf::Vector2f(-normal.y, normal.x) * ((l_anticlockwise) ? 1.0f : -1.0f);

    sf::Vector2f force = (normal + tangent) * (float)constants::k_orbitalCoeff;
    Vec::Restrict(force, (float)constants::k_maxForce);
    return force;
}

sf::Vector2f Boid::CalculateResistanceForce()
{
    sf::Vector2f force = m_velocity * -0.01f * (float)constants::k_resistanceCoeff;
    Vec::Restrict(force, Vec::GetMagnitude(m_velocity));
    return force;
}

void Boid::ApplyForce(sf::Vector2f l_force)
{
    m_acceleration += l_force / m_mass;
}

void Boid::Move(sf::Vector2f l_disp)
{
    m_pos += l_disp;
    if (m_pos.x < 0) { m_pos.x += constants::k_windowSize[0]; }
    else if (m_pos.x > constants::k_windowSize[0]) { m_pos.x -= constants::k_windowSize[0]; }

    if (m_pos.y < 0) { m_pos.y += constants::k_windowSize[1]; }
    else if (m_pos.y > constants::k_windowSize[1]) { m_pos.y -= constants::k_windowSize[1]; }
}

sf::Vector2f Boid::GetPos()
{
    return m_pos;
}

float Boid::GetSpeed()
{
    return Vec::GetMagnitude(m_velocity);
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