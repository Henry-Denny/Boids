#include "Game.hpp"

int main()
{
    Game game({1200, 1200}, "Boids");
    while (!game.IsDone())
    {
        game.HandleInput();
        game.Update();
        game.DrawScene();
        game.RestartClock();
    }
    return 0;
}