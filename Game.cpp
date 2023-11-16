#include "Game.h"


template <class T1, class T2> bool intersection(T1* A, T2* B) {
    return A->getBoundary().left + A->getBoundary().width >= B->getBoundary().left &&
        A->getBoundary().left <= B->getBoundary().left + B->getBoundary().width &&
        A->getBoundary().top + A->getBoundary().height >= B->getBoundary().top &&
        A->getBoundary().top <= B->getBoundary().top + B->getBoundary().height;
}


Game::Game(){
    this->initWindow();
    this->paddle = new Paddle();
    Ball* ball = new Ball (sf::Vector2f{ 1.f,2.f });
    balls.push_back(ball);
    Ball* ball2 = new Ball(1.9f,0.f);
    balls.push_back(ball2);
    balls.emplace_back(new Ball(1.5f,-1.f));
    balls.emplace_back(new Ball(1.5f, 1.f));
    balls.emplace_back(new Ball(1.5f, 1.5f));
    balls.emplace_back(new Ball(1.5f, -1.5f));
    balls.emplace_back(new Ball(1.5f, 3.f));
}

Game::~Game(){    
    balls.erase(balls.begin(), balls.end());
    delete this->paddle;
}

//Basic Functionality
void Game::pollEvent(){
    sf::Event event;
    while (this->window->pollEvent(event)){
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            this->window->close();
    }
    if (event.KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            this->balls.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            this->paddle->paddleMove(1);
            this->paddle->paddleWindowCollision(*this->window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            this->paddle->paddleMove(-1);
            this->paddle->paddleWindowCollision(*this->window);
        }
    }
}

void Game::update(){
    int counter{ 0 };
    for (auto ball : balls) {
        ball->moveBall();
       if (!ball->ballWindowCollision(*this->window)) { 
           std::cout << "ballOut\n"; 
           delete ball;
           balls.erase(balls.begin() + counter);          
       }
       // intersection base on template class
       //if (intersection(paddle, ball)) {
       //    std::cout << "Y";
       //    ball->changeDirection(1, -1);
       //}
       // intersection base on SFML funciotn sf::Rect https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Rect.php
       if (ball->getBoundary().intersects(this->paddle->getBoundary())){
            std::cout << "X";
            ball->changeDirection(1, -1);
       }
       counter++;
    }
}


void Game::draw(){
    window->clear();
    window->draw(*paddle);
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
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}
