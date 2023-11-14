#include "Game.h"

Game::Game(){
    this->initWindow();
    Ball* ball = new Ball();
    balls.push_back(ball);
    Ball* ball2 = new Ball();
    balls.push_back(ball2);
    balls.emplace_back(new Ball());
}

Game::~Game(){
    balls.clear();
}

//Basic Functionality
void Game::pollEvent(){
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||  sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            this->window->close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            this->balls.clear();
    }
}

void Game::update(){
    float i{ -0.5 };
    for (auto ball : balls) {
       ball->moveBall(i, -i);
       i+=0.3f;
    }
}

void Game::draw(){

    window->clear();
    //window.draw(shape);
    for (Ball* ball : balls) {
        window->draw(*ball);
    }
    window->display();
}

bool Game::GameWorking(){
    return this->window->isOpen();
}

void Game::initWindow(){
    
    this->window = new sf::RenderWindow(
        sf::VideoMode(800, 600),
        "Arkanoid!",
        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}
