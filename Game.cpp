#include "Game.h"

Game::Game(){
    this->initWindow();
}

void Game::update(){
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::draw(){

    window->clear();
    //window.draw(shape);
    window->draw(ball);
    window->display();
}

bool Game::GameWorking(){
    return this->window->isOpen();
}

void Game::initWindow(){
    
    this->window = new sf::RenderWindow(
        sf::VideoMode(200, 200),
        "Arkanoid!",
        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}
