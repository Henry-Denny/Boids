#include "Game.hpp"

Game::Game(sf::Vector2u l_winSize, const std::string &l_title) : m_boidManager{}, m_renderer{l_winSize, l_title, &m_boidManager}, m_done{ false }
{
    Setup(l_winSize, l_title);
    Reset();
}

Game::~Game()
{
    // Delete boids
}

void Game::Setup(sf::Vector2u l_winSize, const std::string &l_title)
{
}

void Game::Reset()
{
    // Delete boids
    // Reset to default settings
    m_boidManager.DeleteBoids();
    sf::Vector2u winSize = m_renderer.GetWindow()->getSize();
    for (int i = 0; i < 50; ++i)
    {
        m_boidManager.CreateBoid(winSize.x, winSize.y);
    }
}

void Game::HandleInput()
{
    sf::Event ev;
    while (m_renderer.GetWindow()->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_done = true;
        }
    }
}

void Game::Update()
{
    double deltaTime = m_elapsed.asSeconds();
    // Get delta time, update boid positions
}

void Game::DrawScene()
{
    m_renderer.DrawScene();
}

void Game::RestartClock()
{
    m_elapsed = m_clock.restart();
}

bool Game::IsDone()
{
    return m_done;
}