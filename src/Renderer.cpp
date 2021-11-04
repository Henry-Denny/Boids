#include "Renderer.hpp"

Renderer::Renderer(sf::Vector2u l_winSize, const std::string &l_title, BoidManager *l_boidMgr, sf::Color l_bgCol, int l_framerateLimit)
    : m_boidMgr{l_boidMgr}, m_bgColour{l_bgCol}
{
    m_window.create({l_winSize.x, l_winSize.y}, l_title);
    m_window.setFramerateLimit(l_framerateLimit);
    m_font.loadFromFile("./res/otomanopee.ttf");
    m_fpsText.setFont(m_font);
    m_fpsText.setFillColor(sf::Color::White);
    m_fpsText.setCharacterSize(50);
    m_fpsText.setPosition({30, 30});
}

Renderer::~Renderer() {}

void Renderer::DrawScene(float l_dt)
{
    m_window.clear(m_bgColour);

    DrawBoids();
    DrawOverlay();
    DrawUI(l_dt);

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
        // boidShape.setFillColor(l_boid->GetCol());
        float speed = l_boid->GetSpeed();
        int r = (speed / constants::k_maxSpeed) * 255;
        boidShape.setFillColor({r, 255 - r, 0});
        boidShape.setRotation(l_boid->GetBearing());
        m_window.draw(boidShape);
    }
}

void Renderer::DrawOverlay()
{
    // Draw overlay
}

void Renderer::DrawUI(float l_dt)
{
    m_fpsText.setString("FPS: " + std::to_string(int(1.0f / l_dt)));
    m_window.draw(m_fpsText);
}

sf::RenderWindow* Renderer::GetWindow()
{
    return &m_window;
}