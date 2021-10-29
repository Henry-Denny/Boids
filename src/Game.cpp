#include "Game.hpp"

Game::Game(sf::Vector2u l_winSize, const std::string &l_title)
{
    Setup();
}

Game::~Game()
{
    // Delete boids
}

void Game::Setup()
{
    // Create window
    m_window.setFramerateLimit(60);
}

void Game::Reset()
{
    // Delete boids
    // Reset to default settings
}

void Game::HandleInput()
{
    sf::Event ev;
    while (m_window.pollEvent(ev))
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
    m_window.clear(sf::Color(57, 57, 57));

    // Draw boids

    m_window.display();
}

void Game::RestartClock()
{
    m_elapsed = m_clock.restart();
}

bool Game::IsDone()
{
    return m_done;
}