#include "Game.h"




template <class T1, class T2> bool intersection(T1* A, T2* B) {
    return A->getBoundary().left + A->getBoundary().width >= B->getBoundary().left &&
        A->getBoundary().left <= B->getBoundary().left + B->getBoundary().width &&
        A->getBoundary().top + A->getBoundary().height >= B->getBoundary().top &&
        A->getBoundary().top <= B->getBoundary().top + B->getBoundary().height;
}

template <class T> int intersectByLine(Ball* ball, T* t, sf::Vector2f ballPrevPosition) {
    float ballXp = ballPrevPosition.x;
    float ballYp = ballPrevPosition.y;
    float ballX = ball->getposition().x;
    float ballY = ball->getposition().y;

    float tTop = t->getBoundary().top;
    float tBottom = t->getBoundary().top + t->getBoundary().height;
    float tLeft = t->getBoundary().left;
    float tRight = t->getBoundary().left + t->getBoundary().width;


    // (ballXp - x) / (ballXp- ballX)   = (ballYp - y) (ballYp - ballY)

    if ((ballYp - ballY) == 0) return -1; //ball didnt move ?
    //if (ballY > tTop - 10 && ballY < tTop + 20) 
    {
        int x = ballXp - (((ballYp - tTop) / (ballYp - ballY)) * (ballXp - ballX));
        //std::cout << x;
        if (x >= tLeft && x <= tRight) {
            return 1;
        }
    }
    return -1;
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

    if (ballY > tTop && ballY < tBottom) {
        //( )[===]  left
        if (ballX < tLeft && tLeft-ballX < ballSize){
        //    std::cout << "left";
            return 1;
        }
        //[===]( )  right
        if (ballX > tRight && ballX - tRight < ballSize) {
          //  std::cout << "right";
            return 1;
        }
    }
    else if (ballY + ballSize >= tTop) {
        //   ( )    top
        //  [===]
        if (ballX - ballSize >= tLeft && ballX + ballSize <= tRight) {
            //BallHitDirectlyFrom Top
            //std::cout << "Top";
            return 1;
        }
        //   ( )    topleft
        //    [===]
        else if (ballX + ballSize >= tLeft && ballX - ballSize <= tLeft) {
            if (ballSize * ballSize < (
                (ballY - tTop) * (ballY - tTop) +
                (ballX - tLeft) * (ballX - tLeft)
                )) {
              //  std::cout << "Top Left";
                return 1;
            }

        }
        //       ( )    topright
        //    [===]
        else if (ballX + ballSize >= tRight && ballX - ballSize <= tRight) {
            if (ballSize * ballSize < (
                (ballY - tTop) * (ballY - tTop) +
                (ballX - tRight) * (ballX - tRight)
                )) {
                //std::cout << "Top Right";
                return 1;
            }
        }
        return -1;

    }
    else if (ballY - ballSize <= tBottom) {
        //  [===]
        //   ( )    bottom
        if (ballX - ballSize >= tLeft && ballX + ballSize <= tRight) {
           // std::cout << "Bottom";
            return 1;
        }
        //  [===]
        // ( )    bottomleft
        else if (ballX + ballSize >= tLeft && ballX - ballSize <= tLeft) {
            if ((ballSize * ballSize) < (
                (ballY - tBottom) * (ballY - tBottom) +
                (ballX - tLeft) * (ballX - tLeft)
                )) {
             //   std::cout << "bottom left";
                return 1;
            }
        }
        //  [===]
        //     ( )    bottomright
        else if (ballX + ballSize >= tRight && ballX - ballSize <= tRight) {
            if (ballSize * ballSize < (
                (ballY - tBottom) * (ballY - tBottom) +
                (ballX - tRight) * (ballX - tRight)
                )) {
               // std::cout << "bottom Right";
                return 1;
            }
        }
    }
    return -1;
    
        
}

Game::Game(){
    this->initWindow();
    this->initGUI();
    //std::cout << this->mainFrameCoords.x << std::endl;;
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
    balls.emplace_back(new Ball(90.3f, ballPositon, this->ballSize, 2.f));
    //balls.at(0)->changeDirection(-300.f);
    //balls.emplace_back(new Ball(300.f, sf::Vector2f (20., 20.), this->ballSize, 5.f));

    //balls.emplace_back(new Ball(60.f,ballPositon, this->ballSize, 5.f));
    //balls.emplace_back(new Ball(190.f, ballPositon, this->ballSize, 1.f));
    //balls.emplace_back(new Ball(300.f, ballPositon, this->ballSize, 5.f));
    //balls.emplace_back(new Ball(1.f, -2.f, ballPositon, this->ballSize, 1.f));
    //balls.emplace_back(new Ball(20.6f, -2.f, ballPositon, this->ballSize, 5.f));
    /*
    balls.emplace_back(new Ball(1.5f, -1.f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, 1.f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, 1.5f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, -1.5f, ballPositon, this->ballSize));
    balls.emplace_back(new Ball(1.5f, 3.f, ballPositon, this->ballSize));
    */
}

void Game::initBlocks(){
    //Blocks size
    this->blockWidth = ((this->mainFrameCoords.z - this->mainFrameWidth) - ((this->blocksCols + 1) * this->blockDist)) / this->blocksCols;
    this->blockHight = this->blockWidth * 0.3f;

    for (int r{ 0 }; r < this->blocksRows; r++) {
        std::vector <Block*> temp;
        for (int c{ 0 }; c < this->blocksCols; c++) {
            temp.emplace_back(new Block(
                //point to the center of the block
                c * (this->blockWidth + this->blockDist) + this->blockWidth / 2 + this->blockDist + this->mainFrameWidth,
                r * (this->blockHight + this->blockDist) + this->blockHight / 2 + this->blockDist + this->mainFrameWidth,
                this->blockWidth,
                this->blockHight,
                1));
            this->blockCount++;
            this->mapBlock.emplace(
                std::make_pair(
                    temp.at(c)->getBoundary().left, 
                    temp.at(c)->getBoundary().top), 
                temp.at(c));
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

    this->mainFrameCoords.x = this->mainFrameWidth;
    this->mainFrameCoords.y = this->mainFrameWidth;
    this->mainFrameCoords.z = this->window->getSize().x * 0.9;

    this->mainFrameBottom = this->window->getSize().y - 100.;
    this->paddlePositionY = this->mainFrameBottom;

    this->initMainFrame();
    this->initBlocks();


    //Print map for test purpouse
    //std::cout << std::endl << "Map:" << this->mapBlock.size() << std::endl;
    //for (auto it : this->mapBlock) {
    //    std::cout << "L:" << it.first.first << " T:" << it.first.second << " O:" << it.second << std::endl;
    //}
    //std::cout << "Map-End" << std::endl;
  //  std::cout << "x:" << this->mainFrameCoords.x << " y:" << this->mainFrameCoords.y << " z:" << this->mainFrameCoords.z << std::endl;
}

void Game::initMainFrame(){
    //Left: x,y,w,h
    this->leftWall = new Block(0,0, this->mainFrameWidth, this->window->getSize().y, -1, this->frameColor);
    this->topWall = new Block(0,0, this->mainFrameCoords.z, this->mainFrameWidth, -1, this->frameColor);
    this->rightWall = new Block(this->mainFrameCoords.z,0, this->mainFrameWidth, this->window->getSize().y, -1,this->frameColor);

    
}

bool Game::intersection(Ball* ball, int counter) {
    float ballRange{ ball->getBallVelocity() };
    while (ballRange > 0) {
        //predict new possition
        sf::Vector2f oPos{ ball->getposition() };
        sf::Vector2f nPos{ ball->getBallMovementVector() };
        float ballAlpha{ ball->getBallAlfa() };


        //check if wall will be hitted
        bool hitWall{ false };

        //check direction 
        //going UP
        if (ballAlpha < 180.f) {
            float wallIntersectionY{ 0 };
            float wallIntersectionX{ 0 };
            //MainFrame interaction
            if (nPos.x - this->ballSize < this->mainFrameCoords.x) { //Left Wall
                wallIntersectionY = (oPos.y - nPos.y) * (((oPos.x - this->ballSize) - this->mainFrameCoords.x) / (oPos.x - nPos.x));
            }
            else if (nPos.x + this->ballSize > this->mainFrameCoords.z) { //Right Wall
                wallIntersectionY = (oPos.y - nPos.y) * ((this->mainFrameCoords.z - (oPos.x + this->ballSize)) / (nPos.x - oPos.x));
            }
            if (nPos.y - this->ballSize < this->mainFrameCoords.y) { //Top Wall
                wallIntersectionX = ((nPos.x > oPos.x) ? nPos.x - oPos.x : oPos.x - nPos.x)
                    * (((oPos.y - this->ballSize) - this->mainFrameCoords.y ) / (oPos.y - nPos.y));
            }

            //ball is in blocks range
            if (nPos.y - this->ballSize <= this->mainFrameCoords.y + this->blocksRows * (this->blockDist + this->blockHight)) {
                //check next block lvl if it exist bounce
                //this->mainFrameCoords.y + this->blocksRows * (this->blockDist + this->blockHight)
                for (int i{ this->blocksRows }; i >= 0; i--) {
                    //bottom edge of block:
                    /*
                    //point to the center of the block
                    c* (this->blockWidth + this->blockDist) + this->blockWidth/2 + this->blockDist + this->mainFrameCoords.x,
                    r* (this->blockHight + this->blockDist) + this->blockHight/2 + this->blockDist + this->mainFrameCoords.y,
                    */
                    float bottomBlockEdge{ i * (this->blockDist + this->blockHight) };



                }

            }


        }


        


        return true;
    }
    return false;
}
bool Game::intersection2(Ball* ball, int counter) {
    /*
    * get ball previuos and next position
    * determine direction
    * if ball y variable is within paddle, block, screen, frame check colision
    * what if ball will hit frame before or after hiting other object?
    */
    sf::Vector2f ballPrevPosition = ball->getposition();
    ball->moveBall();
    float ballPositionY = ball->getposition().y;
    float ballPositionX = ball->getposition().x;
    float ballPreviousPositionY = ballPrevPosition.y;
    float ballPreviousPositionX = ballPrevPosition.x;
    bool hitWall{ false };
    
    bool directionUp = (ballPositionY < ballPreviousPositionY) ? true : false;
    //std::cout << directionUp << std::endl; //1 up 0 down
        
    //check if wall will be hitted
    if (ballPositionX - this->ballSize < this->mainFrameCoords.x ||
        ballPositionX + this->ballSize > this->mainFrameCoords.z ||
        ballPositionY - this->ballSize < this->mainFrameCoords.y)
        hitWall = true;

    if (ball->getBallAlfa() < 180.f) {
        //going up, might hit block:
        if (ballPositionY - this->ballSize <
            this->mainFrameCoords.y + this->blocksRows * (this->blockDist + this->blockHight)) {
            std::cout << "Ball on the Blocks lvl    ";
            //check x and verify blocks to be hit (up until ball's end move)
        }
    }
    else {
        if (ballPositionY - this->ballSize <
            this->mainFrameCoords.y + this->blocksRows * (this->blockDist + this->blockHight))
            std::cout << "Block lvl    ";

    }



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
    else if (ballPositionY > this->paddlePositionY - this->paddleSize.y - this->ballSize &&
        ballPositionY < this->paddlePositionY + this->paddleSize.y - this->ballSize)  {
        if (ballPrevPosition != ball->getposition()) {
            int i = intersectByLine(ball, this->paddle, ballPrevPosition);
            //int i = intersectionDir(ball, this->paddle);
            if (i != -1) {
                ball->changeDirection(1, -1);
            }
            //if (ball->getBoundary().intersects(this->paddle->getBoundary())) {
            //    ball->changeDirection(1, -1);
            //}
        }
    }
    //ball lost at the bottom pit
    else if (ballPositionY >= this->windowHeight) {
        std::cout << "ballOut\n";

        ball->ballLost();
        return true;
       /*
        delete ball;
        balls.erase(balls.begin() + counter);
        if (this->balls.size() == 0) {
            this->playerLives--;
            if (this->playerLives <= 0)
                this->gameOver = true;
            else
                this->startNewGame();
        }
        */
    }
    return false;
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


void Game::colisionCheckPhase1X(Ball *ball, std::set<float>* rangeX, std::multimap<std::pair<float, float>, Block*> *secondMap, bool* secondAxis){
    //if it's new list use 0 in x-coords, -1 is reserved for walls etc.
    if (!secondMap->empty()) { //list is not empty
        for (auto sm : *secondMap) {
            // <<colisionX,colisionY>, obj>
            // if map is filled go through each objects
            // if object is too far remove it
            // if object is coliding, fill up X-coords
            if (sm.first.first == 0.) { //value 0 determine that obj was not testen by axis-X
                if ((sm.second->getBoundary().left < *rangeX->begin() && sm.second->getBoundary().left + sm.second->getBoundary().width >= *rangeX->begin()) ||
                    (sm.second->getBoundary().left >= *rangeX->begin() && sm.second->getBoundary().left <= *rangeX->rbegin())) {
                    //std::cout << "W";
                    //detecting direction of ball movement and therefore store top or bottom coords
                    float collisionWall{};
                    if (ball->getBallAlfa() >= 90 && ball->getBallAlfa() < 270) {
                        collisionWall = sm.second->getBoundary().left;
                    }
                    else {
                        collisionWall = sm.second->getBoundary().left + sm.second->getBoundary().width;
                    }
                    secondMap->insert({ std::make_pair(collisionWall,sm.first.second),sm.second });
                }
                std::cout << "M:" << secondMap->size() << "D" << sm.second->getId();
                secondMap->erase(sm.first);
                std::cout << "=" << secondMap->size() << std::endl;
                
                std::cout << std::endl << "Map:" << secondMap->size() << std::endl;
                for (auto it : *secondMap) {
                    std::cout << "X:" << it.first.first << " Y:" << it.first.second << " O:" << it.second->getId() << std::endl;
                }
                std::cout << "Map-End" << std::endl;

            }
        }
    }
    else {
        // <<oX,oY>, obj>
        //std::cout << ">>";
        if (!*secondAxis) {
            for (auto m : this->mapBlock) {
                //going through all blocks defined during initialization process:
                if ((m.second->getBoundary().left <= *rangeX->begin() && m.second->getBoundary().left + m.second->getBoundary().width > *rangeX->begin()) ||
                    (m.second->getBoundary().left > *rangeX->begin() && m.second->getBoundary().left < *rangeX->rbegin())) {
                    //detecting direction of ball movement and therefore store top or bottom coords
                    float collisionWall{};
                    if (ball->getBallAlfa() >= 90 && ball->getBallAlfa() < 270) {
                        collisionWall = m.second->getBoundary().left;
                    }
                    else {
                        collisionWall = m.second->getBoundary().left + m.second->getBoundary().width;
                    }
                    secondMap->insert({ std::make_pair(collisionWall,0.),m.second });
                   // std::cout << ">>" << m.second->getId() << std::endl;

                }
                if (m.first.first > *rangeX->rbegin()) break;
            }
        }
    }
    //std::cout << std::endl << "*X:" << secondMap->size() << ":"<< *secondAxis << std::endl;
    //LWall
    if (this->leftWall->getBoundary().left + this->leftWall->getBoundary().width >= *rangeX->begin() - ball->getSize()) {
        secondMap->insert({ std::make_pair(this->leftWall->getBoundary().left + this->leftWall->getBoundary().width, -1.) , this->leftWall });
    }
    //RWall
    if (this->rightWall->getBoundary().left <= *rangeX->rbegin() + ball->getSize()) {
        secondMap->insert({ std::make_pair(this->rightWall->getBoundary().left, -1.) , this->rightWall });
    }
    *secondAxis = true;
}

void Game::colisionCheckPhase1Y(Ball* ball, std::set<float>* rangeY, std::multimap<std::pair<float, float>, Block*>* secondMap, bool* secondAxis) {
    //if it's new list use 0 in x-coords, -1 is reserved for walls etc.
    if (!secondMap->empty()) { //list is not empty
        for (auto sm : *secondMap) {
            // <<cX,cY>, obj>
            // if map is filled go through each objects
            // if object is too far remove it
            // if object is coliding, go to next object
            //std::cout << "  ->" << sm.first.second << "->" << sm.second->getId()<< "<-" << std::endl;
            if (sm.first.second == 0.) { //if obj. was not checked by axis-Y
                if ((sm.second->getBoundary().top < *rangeY->begin() && sm.second->getBoundary().top + sm.second->getBoundary().height >= *rangeY->begin()) ||
                    (sm.second->getBoundary().top >= *rangeY->begin() && sm.second->getBoundary().top <= *rangeY->rbegin())) {
                    //detecting direction of ball movement and therefore store top or bottom coords
                    float collisionWall{};
                    if (ball->getBallAlfa() >= 0 && ball->getBallAlfa() < 180) {
                        collisionWall = sm.second->getBoundary().top + sm.second->getBoundary().height;
                    }
                    else {
                        collisionWall = sm.second->getBoundary().top;
                    }
                    secondMap->insert({ std::make_pair(sm.first.first,collisionWall),sm.second });
                }
                secondMap->erase(sm.first);
            }
        }
    }
    else {
        // <<oX,oY>, obj>
        //std::cout << ">>";
        if (!*secondAxis) {
            for (auto m : this->mapBlock) {
                //going through all blocks defined during initialization process:
                if ((m.second->getBoundary().top <= *rangeY->begin() && m.second->getBoundary().top + this->blockWidth > *rangeY->begin()) ||
                    (m.second->getBoundary().top > *rangeY->begin() && m.second->getBoundary().top < *rangeY->rbegin())) {
                    //detecting direction of ball movement and therefore store top or bottom coords
                    float collisionWall{};
                    if (ball->getBallAlfa() >= 0 && ball->getBallAlfa() < 180) {
                        collisionWall = m.second->getBoundary().top + m.second->getBoundary().height;
                    }
                    else {
                        collisionWall = m.second->getBoundary().top;
                    }
                    secondMap->insert({ std::make_pair(0.,collisionWall),m.second });
                }
                if (m.first.second > *rangeY->rbegin()) break;
            }
        }
    }
    //TopWall
    if (this->topWall->getBoundary().height >= *rangeY->begin() - ball->getSize()) {
        secondMap->insert({ std::make_pair(-1.,this->topWall->getBoundary().top + this->topWall->getBoundary().height) , this->topWall });
    }
    //std::cout << "  *Y:" << secondMap->size() << "*" ;
    *secondAxis = true;
}
void Game::colisionCheckPhase2(Ball* ball, std::set<float>* rangeX, std::set<float>* rangeY, std::multimap<std::pair<float, float>, Block*>* secondMap) {
    std::cout << std::endl<<  secondMap->size() << "-";
    for (auto sm : *secondMap) {
        //std::cout << sm.second->getId() << std::endl;
        sm.second->setcolor(sf::Color::White);////////
        std::cout << ">>" << sm.second->getId() << " "  << sm.first.first << "x" << sm.first.second << std::endl;
    }
}
void Game::colisionAlgorithm(Ball* ball) {
    bool secondAxis{ false };
    std::multimap<std::pair<float, float>, Block*>* secondMap = new (std::multimap<std::pair<float, float>, Block*>);
    sf::Vector2f ballFirstPosition = ball->getposition();
    sf::Vector2f ballSecondPosition = ball->predictPosition();
    std::set<float> rangeX{ ballFirstPosition.x, ballSecondPosition.x };
    std::set<float> rangeY{ ballFirstPosition.y, ballSecondPosition.y };
    if (*rangeX.rbegin() > 0 && *rangeY.rbegin() > 0) {
       /*
        std::cout << std::endl;

        std::cout << "X-";
        for (auto a : rangeX) {
            std::cout << a << " ";
        }
        std::cout << "Y-";
        for (auto a : rangeY) {
            std::cout << a << " ";
        }
        std::cout << std::endl;
        */
        colisionCheckPhase1Y(ball, &rangeY, secondMap, &secondAxis);
        colisionCheckPhase1X(ball, &rangeX, secondMap, &secondAxis);
        if(!secondMap->empty()) colisionCheckPhase2(ball, &rangeX, &rangeY, secondMap);
        /*
        std::cout << std::endl;
        if (secondMap->size() > 0) { //<<cX,cY>, obj>
            std::cout << secondMap->size() << std::endl;
            for (auto a : *secondMap) {
                std::cout << " X: " << a.first.first << ", Y: " << a.first.second << std::endl;
            }
        }
        */
    }
    ball->moveBall();
    delete secondMap;
}

void Game::update() {
    if (!this->gameOver) {
        int counter{ 0 };
        bool ballLost{ false };
        for (auto ball : balls) {
            //check if ball movement is within specific range y
            //use x or y (smaller) to create list of potential colision
            //use anoter axis for determining if collision is taking place
            //with specific object verify collision and it's aftermovement
            //check for this object if new collision is possible (back to step 1)

            colisionAlgorithm(ball);

            if (intersection(ball, counter)) ballLost = true;  //counter can be discarded
            counter++;
        }
        for (auto it{ balls.begin() }; it != balls.end(); ) {
            if ((*it)->getLostBall()) {
                delete* it;
                it = balls.erase(it);
            }
            else it++;
        }

        if (this->balls.size() == 0) {
            this->playerLives--;
            if (this->playerLives <= 0)
                this->gameOver = true;
            else
                this->startNewGame();
        }
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
    //for (auto w : walls) {
    //    window->draw(*w);
    //}
    window->draw(*this->leftWall);
    window->draw(*this->topWall);
    window->draw(*this->rightWall);

    for (auto r : blocks) {
        for (auto b : r) {
            if (b->printableObj())
                window->draw(*b);
        }
    }
    window->draw(*paddle);
    for (Ball* ball : balls) {
        window->draw(*ball);
        ball->restoreMovement();
    }
    //window->draw(*this->mainFrame);

    window->display();
   //std::cout << "x:" << this->mainFrameCoords.x << " y:" << this->mainFrameCoords.y << " z:" << this->mainFrameCoords.z << std::endl;

}
