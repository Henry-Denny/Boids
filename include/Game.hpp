#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game(sf::Vector2u l_winSize, const std::string &l_title);
    ~Game();

    void Setup(sf::Vector2u l_winSize, const std::string &l_title);
    void Reset();

    void HandleInput();
    void Update();
    void DrawScene();
    void RestartClock();

    bool IsDone();

private:
    bool m_done;
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
};

#endif