#include "Game.hpp"
#include "Constants.hpp"

int main()
{
    using namespace constants;
    Game game({k_windowSize[0], k_windowSize[1]}, "Boids");
    while (!game.IsDone())
    {
        game.HandleInput();
        game.Update();
        game.DrawScene();
        game.RestartClock();
    }
    return 0;
}