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
    Ball* ball = new Ball (sf::Vector2f{ 0.f,-2.f });
    balls.push_back(ball);
    Ball* ball2 = new Ball(1.9f,0.f);
    balls.push_back(ball2);
    balls.emplace_back(new Ball(1.5f, -1.f));
    balls.emplace_back(new Ball(1.5f, 1.f));
    balls.emplace_back(new Ball(1.5f, 1.5f));
    balls.emplace_back(new Ball(1.5f, -1.5f));
    balls.emplace_back(new Ball(1.5f, 3.f));
    
    //this->block = new Block(400, 80, 60,20);
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
       else {
           bool hitBlock{ false };
           for (size_t r{ 0 }; r < blocks.size() && !hitBlock; r++) {
               for (size_t c{ 0 }; c < blocks.at(r).size() && !hitBlock; c++) {
                   if (ball->getBoundary().intersects(blocks.at(r).at(c)->getBoundary())) {
                       delete blocks.at(r).at(c);
                       blocks.at(r).erase(blocks.at(r).begin() + c);
                       std::cout << "hit!";
                       ball->changeDirection(-1, -1);
                   }
               }
           }
       }
       counter++;
    }
}


void Game::draw(){
    window->clear();
    
    //window->draw(*this->block);
    for (auto r : blocks) {
        for (auto b : r) {
           // if(b != nullptr) 
                if(b->printableObj())
                    window->draw(*b);
        }
    }
    window->draw(*paddle);
    for (Ball* ball : balls) {
        window->draw(*ball);
    }
    
    //TEST VVVVV

    sf::VertexArray triangleStrip (sf::TriangleStrip);
    sf::Color col = sf::Color::Blue;
    triangleStrip.append(sf::Vertex(sf::Vector2f(10, 10), col)); //1
    triangleStrip.append(sf::Vertex(sf::Vector2f(30, 10), col)); //2
    triangleStrip.append(sf::Vertex(sf::Vector2f(10, 590), col)); //3
    triangleStrip.append(sf::Vertex(sf::Vector2f(30, 570), col)); //4
    triangleStrip.append(sf::Vertex(sf::Vector2f(990, 590), col)); //5
    triangleStrip.append(sf::Vertex(sf::Vector2f(970, 570), col)); //6
    triangleStrip.append(sf::Vertex(sf::Vector2f(990, 10), col)); //7
    triangleStrip.append(sf::Vertex(sf::Vector2f(970, 10), col)); //8


    window->draw(triangleStrip);
    //TEST AAAAAAA


    window->display();
}

bool Game::GameWorking(){
    return this->window->isOpen();
}

void Game::initBlocks(){
    std::cout << this->blockWidth << std::endl;
    for (int r{ 0 }; r < this->blocksRows; r++) {
        std::vector <Block*> temp;
        for (int c{ 0 }; c < this->blocksCols; c++) {
            temp.emplace_back( new Block(
                c* this->blockWidth + this->blockWidth/2 + this->blockDist + c*this->blockDist,
                r* this->blockHight + this->blockHight/2 + this->blockDist + r*this->blockDist,
                this->blockWidth, 
                this->blockHight));
        }
        this->blocks.push_back(temp);
        //temp.clear();
    }
}

void Game::initWindow(){

    //this->lines[0].position = sf::Vector2f(10, 0);
    //this->lines[1].position = sf::Vector2f(100, 0);

    this->window = new sf::RenderWindow(
        sf::VideoMode(this->windowWidth, this->windowHeight),
        "Arkanoid!",
        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);

    this->initBlocks();
}
