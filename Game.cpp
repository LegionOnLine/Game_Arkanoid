#include "Game.h"


template <class T1, class T2> bool intersection(T1* A, T2* B) {
    return A->getBoundary().left + A->getBoundary().width >= B->getBoundary().left &&
        A->getBoundary().left <= B->getBoundary().left + B->getBoundary().width &&
        A->getBoundary().top + A->getBoundary().height >= B->getBoundary().top &&
        A->getBoundary().top <= B->getBoundary().top + B->getBoundary().height;
}


Game::Game(){
    this->initWindow();
    this->paddle = new Paddle(this->mainFrameCoords.x + this->mainFrameCoords.z);
    startNewGame();
}

Game::~Game(){    
    balls.erase(balls.begin(), balls.end());
    delete this->paddle;
}

bool Game::GameWorking() {

    return this->window->isOpen();
}

//Basic Functionality

void Game::startNewGame(){
    balls.emplace_back(new Ball(1.9f, 0.f, this->paddle->getPosition()));
    balls.emplace_back(new Ball(0.f, -2.f, this->paddle->getPosition()));
    balls.emplace_back(new Ball(1.5f, -1.f, this->paddle->getPosition()));
    balls.emplace_back(new Ball(1.5f, 1.f, this->paddle->getPosition()));
    balls.emplace_back(new Ball(1.5f, 1.5f, this->paddle->getPosition()));
    balls.emplace_back(new Ball(1.5f, -1.5f, this->paddle->getPosition()));
    balls.emplace_back(new Ball(1.5f, 3.f, this->paddle->getPosition()));
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
    this->window = new sf::RenderWindow(
        sf::VideoMode(this->windowWidth, this->windowHeight),
        "Arkanoid!",
        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);

    this->initMainFrame();
    this->initBlocks();
}

void Game::initMainFrame(){
    this->frameColor = sf::Color::Blue;
    this->mainFrameCoords.x = 10.;
    this->mainFrameCoords.y = 10.;
    this->mainFrameCoords.z = this->window->getSize().x - 100.;

    this->mainFrameBottom = this->window->getSize().y - 100.;
    this->mainFrameWidth = 10;

    this->mainFrame = new sf::VertexArray(sf::TriangleStrip);

    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x - this->mainFrameWidth, this->mainFrameBottom), this->frameColor)); //1
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x, this->mainFrameBottom), this->frameColor)); //2
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x - this->mainFrameWidth, this->mainFrameCoords.y - this->mainFrameWidth), this->frameColor)); //3
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x, this->mainFrameCoords.y), this->frameColor)); //4
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z + this->mainFrameWidth, this->mainFrameCoords.y - this->mainFrameWidth), this->frameColor)); //5
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z, this->mainFrameCoords.y), this->frameColor)); //6
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z + this->mainFrameWidth, this->mainFrameBottom), this->frameColor)); //7
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z , this->mainFrameBottom), this->frameColor)); //8
}

void Game::pollEvent() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            this->window->close();
    }
    if (event.KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            this->balls.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            this->paddle->paddleMove(1);
            //this->paddle->paddleWindowCollision(*this->window);
            this->paddle->paddleFrameCollision(this->mainFrameCoords);
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            this->paddle->paddleMove(-1);
            //this->paddle->paddleWindowCollision(*this->window);
            this->paddle->paddleFrameCollision(this->mainFrameCoords);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            //release stacked ball
            for (auto ball : balls) {
                if (ball->isBallStuck()) ball->ballRelease();
            }
        }
    }
}

void Game::update() {
    int counter{ 0 };
    for (auto ball : balls) {
        ball->moveBall();
        //if (!ball->ballWindowCollision(*this->window)) {
        if (ball->ballLost(this->window->getSize().y)) {
            std::cout << "ballOut\n";
            delete ball;
            balls.erase(balls.begin() + counter);
        }
        else
            ball->ballFrameCollision(this->mainFrameCoords);
        // intersection base on template class
        //if (intersection(paddle, ball)) {
        //    std::cout << "Y";
        //    ball->changeDirection(1, -1);
        //}
        // intersection base on SFML funciotn sf::Rect https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Rect.php
        if (ball->getBoundary().intersects(this->paddle->getBoundary())) {
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


void Game::draw() {
    window->clear();

    //window->draw(*this->block);
    for (auto r : blocks) {
        for (auto b : r) {
            // if(b != nullptr) 
            if (b->printableObj())
                window->draw(*b);
        }
    }
    window->draw(*paddle);
    for (Ball* ball : balls) {
        window->draw(*ball);
    }

    //TEST VVVVV


    window->draw(*this->mainFrame);
    //TEST AAAAAAA


    window->display();
}
