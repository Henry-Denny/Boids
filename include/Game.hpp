#ifndef GAME_HPP
#define GAME_HPP

#include "Renderer.hpp"
#include "BoidManager.hpp"
#include "Behaviours.hpp"

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game(sf::Vector2u l_winSize, const std::string &l_title);
    ~Game();

    void Reset();

    void HandleInput();
    void Update();
    void DrawScene();
    void RestartClock();

    bool IsDone();

private:
    bool m_done;

    BoidManager m_boidManager;
    Renderer m_renderer;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    std::uint8_t m_behaviours;
};

#endif