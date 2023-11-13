#include <SFML/Graphics.hpp>
#include "Game.h"

#include "Ball.h"

int main()
{
    Game game;
    Ball ball;
    while (game.GameWorking()){
        game.update();
        game.draw();
    }

    return 0;
}