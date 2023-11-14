#include "Game.h"


int main()
{
    Game game;

    while (game.GameWorking()){
        game.pollEvent();
        game.update();
        game.draw();
    }

    return 0;
}