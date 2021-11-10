#ifndef BOID_MANAGER_HPP
#define BOID_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Boid.hpp"

class BoidManager
{
public:
    BoidManager();
    ~BoidManager();

    void DeleteBoids();
    void CreateBoid(sf::Vector2f l_pos);
    void CreateBoid(unsigned int l_winWidth, unsigned int l_winHeight);
    void Step(double dt, std::uint8_t behaviourOptions = 0b11111111);

    void ToggleOrbitalDirection();

    const std::vector<Boid*>& GetFlock();

private:
    std::vector<Boid*> m_flock;
    bool m_anticlockwiseOrbit;
};

#endif