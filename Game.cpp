#include "Game.h"

template <class T1, class T2> bool intersection(T1* A, T2* B) {
    return A->getBoundary().left + A->getBoundary().width >= B->getBoundary().left &&
        A->getBoundary().left <= B->getBoundary().left + B->getBoundary().width &&
        A->getBoundary().top + A->getBoundary().height >= B->getBoundary().top &&
        A->getBoundary().top <= B->getBoundary().top + B->getBoundary().height;
}

template <class T> int intersectionDir(Ball* ball, T* t) {
    float ballX = ball->getposition().x;
    float ballY = ball->getposition().y;
    float ballSize = ball->getSize();
    // this->ballSize;
    float tTop = t->getBoundary().top;
    float tBottom = t->getBoundary().top + t->getBoundary().height;
    float tLeft = t->getBoundary().left;
    float tRight = t->getBoundary().left + t->getBoundary().width;

    //top
    if (ballY + ballSize >= tTop) {
        //  (             )
        //  [=============]
        if (ballX - ballSize >= tLeft && ballX + ballSize <= tRight) { 
            //BallHitDirectlyFrom Top
            std::cout<< "Top";
            return 1;
        }
        //  (             )
        //     [=============]
        else if (ballX + ballSize >= tLeft && ballX - ballSize <= tLeft) {
            if (ballSize * ballSize < (
                (ballY - tTop) * (ballY - tTop) +
                (ballX - tLeft) * (ballX - tLeft)
                )) {
                std::cout << "Top Left";
                return 1;
            }

        }
            //     (             )
            //  [=============]
        else if (ballX + ballSize >= tRight && ballX - ballSize <= tRight) {
            if (ballSize * ballSize < (
                (ballY - tTop) * (ballY - tTop) +
                (ballX - tRight) * (ballX - tRight)
                )) {
                std::cout <<"Top Right";
                return 1;
            }
        }
        return -1;

    }
    //topleft
    //topright
    //bottom
    //bottomright
    //bottomleft
    //right
    //left
}

Game::Game(){
    this->initWindow();
    this->initGUI();
    std::cout << this->mainFrameCoords.x << std::endl;;
    this->paddle = new Paddle(
        (this->mainFrameCoords.z - this->mainFrameCoords.x)/2,
        this->paddlePositionY,
        this->paddleSize);
    std::cout << (this->mainFrameCoords.z - this->mainFrameCoords.x) / 2; //795 = (1600 - 10) /2
    if (!this->gameOver) {
        startNewGame();
    }
}

Game::~Game(){    
    balls.erase(balls.begin(), balls.end());
    delete this->paddle;
}

bool Game::GameWorking() {

    return this->window->isOpen();
}

//Basic Functionality

void Game::initGUI(){
    if (!this->font.loadFromFile("./Fonts/TheLightFont.ttf"))
        std::cout << "ERROR::Text Font Load Problem" << std::endl;

    //init point text
    this->textPoints.setPosition(this->window->getSize().x - 100, 25.f);
    this->textPoints.setFont(this->font);
    this->textPoints.setCharacterSize(20);
    this->textPoints.setFillColor(sf::Color::White);

    //init lives text
    this->textLives.setPosition(this->window->getSize().x - 100, 50.f);
    this->textLives.setFont(this->font);
    this->textLives.setCharacterSize(20);
    this->textLives.setFillColor(sf::Color::White);

    this->textGame.setPosition(this->window->getSize().x/2-100, this->window->getSize().y / 2-50);
    this->textGame.setFont(this->font);
    this->textGame.setCharacterSize(60);
    this->textGame.setFillColor(sf::Color::Red);
}

void Game::startNewGame(){
    //balls.emplace_back(new Ball(1.9f, 0.f, this->paddle->getPosition()));
    sf::Vector2f ballPositon = { this->paddle->getPosition().x, 
        this->paddlePositionY - this->paddleSize.y/2  };
    balls.emplace_back(new Ball(0.f, -2.f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, -1.f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, 1.f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, 1.5f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, -1.5f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, 3.f, ballPositon, this->ballSize));
}

void Game::initBlocks(){
    for (int r{ 0 }; r < this->blocksRows; r++) {
        std::vector <Block*> temp;
        for (int c{ 0 }; c < this->blocksCols; c++) {
            temp.emplace_back( new Block(
                //point to the center of the block
                c* (this->blockWidth + this->blockDist) + this->blockWidth/2 + this->blockDist + this->mainFrameCoords.x,
                r* (this->blockHight + this->blockDist) + this->blockHight/2 + this->blockDist + this->mainFrameCoords.y,
                this->blockWidth, 
                this->blockHight));
            this->blockCount++;
        }
        this->blocks.push_back(temp);
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
    this->mainFrameCoords.z = this->window->getSize().x - 200.;

    this->mainFrameBottom = this->window->getSize().y - 100.;
    this->paddlePositionY = this->mainFrameBottom;
    this->mainFrameWidth = 10;

    this->mainFrame = new sf::VertexArray(sf::TriangleStrip);

    //this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x - this->mainFrameWidth, this->mainFrameBottom), this->frameColor)); //1
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x - this->mainFrameWidth, this->windowHeight), this->frameColor)); //1
    //this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x, this->mainFrameBottom), this->frameColor)); //2
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x, this->windowHeight), this->frameColor)); //2
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x - this->mainFrameWidth, this->mainFrameCoords.y - this->mainFrameWidth), this->frameColor)); //3
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.x, this->mainFrameCoords.y), this->frameColor)); //4
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z + this->mainFrameWidth, this->mainFrameCoords.y - this->mainFrameWidth), this->frameColor)); //5
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z, this->mainFrameCoords.y), this->frameColor)); //6
    //this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z + this->mainFrameWidth, this->mainFrameBottom), this->frameColor)); //7
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z + this->mainFrameWidth, this->windowHeight), this->frameColor)); //7
    //this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z, this->mainFrameBottom), this->frameColor)); //8
    this->mainFrame->append(sf::Vertex(sf::Vector2f(this->mainFrameCoords.z, this->windowHeight), this->frameColor)); //8
    //Blocks size
    this->blockWidth = ((this->mainFrameCoords.z - this->mainFrameCoords.x - this->mainFrameWidth) - (this->blocksCols * this->blockDist)) / this->blocksCols;
    this->blockHight = this->blockWidth * 0.3f;
}


void Game::intersection(Ball* ball, int counter){
    ball->moveBall();
    float ballPositionY = ball->getposition().y;
    float ballPositionX = ball->getposition().x;

    float ballRangeTop = ballPositionY - this->ballSize - this->blockHight;
    float ballRangeBottom = ballPositionY + this->ballSize + this->blockHight;

    //ball hitting sides
    if (ballPositionX - this->ballSize <= this->mainFrameCoords.x || 
        ballPositionX + this->ballSize >= this->mainFrameCoords.z) {
        ball->changeDirection(-1, 1);
    }
    //ball hitting top
    if (ballPositionY - this->ballSize <= this->mainFrameCoords.y) {
        ball->changeDirection(1, -1);
    }
    //ball hitting block
    //range ballpositionY-ballsize-blockheight : ballpositionY+ballsize+blockheight
    //r* (this->blockHight + this->blockDist) + this->blockHight / 2 + this->blockDist + this->mainFrameCoords.y,
    else if (ballPositionY - this->ballSize <= this->blocksRows * (this->blockHight + this->blockDist) + this->mainFrameCoords.y) {
        bool hitBlock{ false };
        for (size_t r{ 0 }; r < blocks.size() && !hitBlock; r++) {
            for (size_t c{ 0 }; c < blocks.at(r).size() && !hitBlock; c++) {
                if (ball->getBoundary().intersects(blocks.at(r).at(c)->getBoundary())) {
                    this->playerPoints += blocks.at(r).at(c)->getPoints();
                    delete blocks.at(r).at(c);
                    blocks.at(r).erase(blocks.at(r).begin() + c);
                    ball->changeDirection(-1, -1);
                    this->blockCount--;
                    std::cout << "hit! - " << this->blockCount << std::endl;
                    if (this->blockCount <= 0)
                        this->initBlocks();
                }
            }
        }
    }
    //ball hitting Paddle
    else if (ballPositionY > this->paddlePositionY - this->paddleSize.y - this->ballSize) {
        int i = intersectionDir(ball, this->paddle);
        if (ball->getBoundary().intersects(this->paddle->getBoundary())) {
            ball->changeDirection(1, -1);
        }
    }    
    //ball lost at the bottom pit
    else if (ballPositionY >= this->windowHeight) {
        std::cout << "ballOut\n";
        delete ball;
        balls.erase(balls.begin() + counter);
        if (this->balls.size() == 0) {
            this->playerLives--;
            if (this->playerLives <= 0)
                this->gameOver = true;
            else
                this->startNewGame();
        }
    }
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
        intersection(ball, counter);
        counter++;
    }
}

void Game::updateGui(){
    std::stringstream ssPoints;
    ssPoints << "Points: " << this->playerPoints;
    this->textPoints.setString(ssPoints.str());

    std::stringstream ssLives;
    ssLives << "Lives: " << this->playerLives;
    this->textLives.setString(ssLives.str());
}

void Game::updateGameText(){
    std::stringstream ss;
    ss << "Game Over";
    this->textGame.setString(ss.str());
}

void Game::renderGui() {
    this->updateGui();

    this->window->draw(this->textPoints);
    this->window->draw(this->textLives);
    if (this->gameOver) {
        this->updateGameText();
        this->window->draw(this->textGame);
    }
}

void Game::draw() {
    window->clear();

    this->renderGui();
    for (auto r : blocks) {
        for (auto b : r) {
            if (b->printableObj())
                window->draw(*b);
        }
    }
    window->draw(*paddle);
    for (Ball* ball : balls) {
        window->draw(*ball);
    }
    window->draw(*this->mainFrame);

    window->display();
}
