#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Boid.hpp"
#include "BoidManager.hpp"

#include <SFML/Graphics.hpp>

#include <random>
#include <vector>
#include <string>

class Renderer
{
public:
    Renderer(sf::Vector2u l_winSize, const std::string &l_title, BoidManager *l_boidMgr, sf::Color l_bgCol = {57, 57, 57}, int l_framerateLimit = 60);
    ~Renderer();

    void DrawScene(float l_dt);
    sf::RenderWindow* GetWindow();

private:
    void DrawBoids();
    void DrawOverlay();
    void DrawUI(float l_dt);

    BoidManager *m_boidMgr;
    sf::RenderWindow m_window;
    sf::Color m_bgColour;
    sf::Font m_font;
    sf::Text m_fpsText;
};

#endif