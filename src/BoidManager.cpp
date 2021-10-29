#include "BoidManager.hpp"

BoidManager::BoidManager()
{

}

BoidManager::~BoidManager()
{
    DeleteBoids();
}

void BoidManager::CreateBoid(sf::Vector2f l_pos)
{
    // Allocate memory and push boid onto vector
    Boid *boid = new Boid(l_pos);
    m_boids.push_back(boid);
}

void BoidManager::DeleteBoids()
{
    // Deallocate memory
    for (auto &boid : m_boids)
    {
        delete boid;
        boid = nullptr;
    }
    m_boids.clear();
}