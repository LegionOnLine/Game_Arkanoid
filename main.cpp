#include "Game.h"
#include "gTest.h"

bool TESTS{ true };

int main(int argc, char* argv[]){
    sf::Style::None;
    if (TESTS) {
        return mainTest(argc, argv);
    }
    Game game;
    /*
    float angle = 5.f;
    //std::cout << angle << " x - " << game.collisionRespond(angle, 'x') << std::endl;
    std::cout << angle << " y - " << game.collisionRespond(angle, 'y') << std::endl;
    angle = 95.f;
    std::cout << angle << " x - " << game.collisionRespond(angle, 'x') << std::endl;
    //std::cout << angle << " y - " << game.collisionRespond(angle, 'y') << std::endl;
    angle = 185.f;
    //std::cout << angle << " x - " << game.collisionRespond(angle, 'x') << std::endl;
    std::cout << angle << " y - " << game.collisionRespond(angle, 'y') << std::endl;
    angle = 275.f;
    std::cout << angle << " x - " << game.collisionRespond(angle, 'x') << std::endl;
    //std::cout << angle << " y - " << game.collisionRespond(angle, 'y') << std::endl;
    */
    while (game.GameWorking()){
        game.pollEvent();
        game.update();
        game.draw();
    }

    return 0;
}