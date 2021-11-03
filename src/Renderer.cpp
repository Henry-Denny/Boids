#include "Renderer.hpp"

Renderer::Renderer(sf::Vector2u l_winSize, const std::string &l_title, BoidManager *l_boidMgr, sf::Color l_bgCol, int l_framerateLimit)
    : m_boidMgr{l_boidMgr}, m_bgColour{l_bgCol}
{
    m_window.create({l_winSize.x, l_winSize.y}, l_title);
    m_window.setFramerateLimit(l_framerateLimit);
}

Renderer::~Renderer() {}

void Renderer::DrawScene()
{
    m_window.clear(m_bgColour);

    DrawBoids();
    DrawOverlay();

    m_window.display();
}

void Renderer::DrawBoids()
{
    const auto &l_flock = m_boidMgr->GetFlock();
    if (l_flock.empty()) { return; }
    for (const auto &l_boid : l_flock)
    {
        sf::ConvexShape boidShape{ 3 };
        sf::Vector2f origin = l_boid->GetPos();
        boidShape.setPosition(origin);
        boidShape.setOrigin(origin);
        boidShape.setPoint(0, origin + sf::Vector2f(0, -12));
        boidShape.setPoint(1, origin + sf::Vector2f(-6, 6));
        boidShape.setPoint(2, origin + sf::Vector2f(6, 6));
        boidShape.setFillColor({rand() % 256, rand() % 256, rand() % 256});
        m_window.draw(boidShape);
    }
}

void Renderer::DrawOverlay()
{
    // Draw overlay
}

sf::RenderWindow* Renderer::GetWindow()
{
    return &m_window;
}