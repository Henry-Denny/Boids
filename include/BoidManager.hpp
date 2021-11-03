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

    const std::vector<Boid*>& GetFlock();

private:
    std::vector<Boid*> m_flock;


};

#endif