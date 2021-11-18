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

    for (int i = 0; i < m_behavioursText.size(); ++i)
    {
        m_behavioursText[i].setFont(m_font);
        m_behavioursText[i].setFillColor(sf::Color::White);
        m_behavioursText[i].setCharacterSize(20);
        m_behavioursText[i].setPosition(sf::Vector2f(constants::k_windowSize[0] - 200, 30) + sf::Vector2f(0, i * 40));
    }
    m_behavioursText[0].setString("1: Alignment");
    m_behavioursText[1].setString("2: Cohesion");
    m_behavioursText[2].setString("3: Avoidance");
    m_behavioursText[3].setString("4: Centralisation");
    m_behavioursText[4].setString("5: Orbit");
    m_behavioursText[5].setString("6: Resistance (air)");
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

void Renderer::UpdateBehaviourText(uint8_t l_behaviours)
{
    for (int i = 0; i < m_behavioursText.size(); ++i)
    {
        m_behavioursText[i].setFillColor(sf::Color(70, 70, 70));
    }
    if (l_behaviours & (std::uint8_t)Behaviour::Alignment)
    {
        m_behavioursText[0].setFillColor(sf::Color::White);
    }
    if (l_behaviours & (std::uint8_t)Behaviour::Cohesion)
    {
        m_behavioursText[1].setFillColor(sf::Color::White);
    }
    if (l_behaviours & (std::uint8_t)Behaviour::Separation)
    {
        m_behavioursText[2].setFillColor(sf::Color::White);
    }
    if (l_behaviours & (std::uint8_t)Behaviour::Centralisation)
    {
        m_behavioursText[3].setFillColor(sf::Color::White);
    }
    if (l_behaviours & (std::uint8_t)Behaviour::Orbit)
    {
        m_behavioursText[4].setFillColor(sf::Color::White);
    }
    if (l_behaviours & (std::uint8_t)Behaviour::Resistance)
    {
        m_behavioursText[5].setFillColor(sf::Color::White);
    }
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
        boidShape.setPoint(0, origin + sf::Vector2f(0, -16));
        boidShape.setPoint(1, origin + sf::Vector2f(-8, 8));
        boidShape.setPoint(2, origin + sf::Vector2f(8, 8));
        // boidShape.setFillColor(l_boid->GetCol());
        float speed = l_boid->GetSpeed();
        int r = (speed / constants::k_maxSpeed) * 255;
        boidShape.setFillColor({sf::Uint8(r), sf::Uint8(255 - r), 0});
        boidShape.setRotation(l_boid->GetBearing());
        m_window.draw(boidShape);
    }
}

void Renderer::DrawOverlay()
{
    const auto &l_flock = m_boidMgr->GetFlock();
    if (l_flock.empty()) { return; }
    for (const auto &l_boid : l_flock)
    {
        for (const auto &other : l_flock)
        {
            if (other == l_boid) { continue; }
            if (Vec::Distance(l_boid->GetPos(), other->GetPos()) > constants::k_visionRadius) { continue; }
            if (std::abs(l_boid->GetBearing() - other->GetBearing()) > constants::k_visionAngle) { continue; }
            sf::Vertex line[] =
            {
                sf::Vertex(l_boid->GetPos(), sf::Color::White),
                sf::Vertex(other->GetPos(), sf::Color::Black)
            };
            m_window.draw(line, 2, sf::Lines);
        }
    }
}

void Renderer::DrawUI(float l_dt)
{
    m_fpsText.setString("FPS: " + std::to_string(int(1.0f / l_dt)));
    m_window.draw(m_fpsText);

    for (const sf::Text &text : m_behavioursText)
    {
        m_window.draw(text);
    }
}

sf::RenderWindow* Renderer::GetWindow()
{
    return &m_window;
}