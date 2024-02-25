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
        this->paddleLevel,
        this->paddleSize);
    //std::cout << (this->mainFrameCoords.z - this->mainFrameCoords.x) / 2; //795 = (1600 - 10) /2
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
        this->paddleLevel - this->paddleSize.y/2 -1 };
    balls.emplace_back(new Ball(this->alpha, ballPositon, this->ballSize,this->ballSpeed)); //69.9
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
  //  std::cout << "blockWidth: "<< this->blockWidth << std::endl;
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
    this->paddleLevel = this->mainFrameBottom;

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
    //ball->moveBall();
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
           // std::cout << "Ball on the Blocks lvl    ";
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
                   // std::cout << "hit! - " << this->blockCount << std::endl;
                    if (this->blockCount <= 0)
                        this->initBlocks();
                }
            }
        }
    }
    //ball hitting Paddle
    else if (ballPositionY > this->paddleLevel - this->paddleSize.y - this->ballSize &&
        ballPositionY < this->paddleLevel + this->paddleSize.y - this->ballSize)  {
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
       // std::cout << "ballOut\n";

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
    if (!secondMap->empty()) { //list is not empty
        std::multimap<std::pair<float, float>, Block*> tempMap{};
        for (auto sm{secondMap->cbegin()}, nsm{sm}; sm != secondMap->cend(); sm = nsm) {
            nsm++;
            if (sm->first.first == 0.) {
                if ((sm->second->getBoundary().left < *rangeX->begin() && sm->second->getBoundary().left + sm->second->getBoundary().width >= *rangeX->begin()) ||
                    (sm->second->getBoundary().left >= *rangeX->begin() && sm->second->getBoundary().left <= *rangeX->rbegin())) {
                    float collisionWall{};
                    if (ball->getBallAlfa() >= 90 && ball->getBallAlfa() < 270) {
                        collisionWall = sm->second->getBoundary().left;
                    }
                    else {
                        collisionWall = sm->second->getBoundary().left + sm->second->getBoundary().width;
                    }
                    tempMap.insert({ std::make_pair(collisionWall,sm->first.second),sm->second });
                }
                secondMap->erase(sm);
            }
        }
        if (!tempMap.empty()) {
            for (auto t : tempMap) {
                secondMap->insert(t);
            }
        }
    }
    else {
        // <<oX,oY>, obj>
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
                }
                if (m.first.first > *rangeX->rbegin()+ this->ballSize) break;
            }
        }
    }
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
        std::multimap<std::pair<float, float>, Block*> tempMap{};
        for (auto sm{ secondMap->cbegin() }, nsm{ sm }; sm != secondMap->cend(); sm = nsm) {
            nsm++;
            if (sm->first.second == 0.) {
                if ((sm->second->getBoundary().top < *rangeY->begin() && sm->second->getBoundary().top + sm->second->getBoundary().height >= *rangeY->begin()) ||
                    (sm->second->getBoundary().top >= *rangeY->begin() && sm->second->getBoundary().top <= *rangeY->rbegin())) {
                    float collisionWall{};
                    if (ball->getBallAlfa() >= 0 && ball->getBallAlfa() < 180) {
                        collisionWall = sm->second->getBoundary().top + sm->second->getBoundary().height;
                    }
                    else {
                        collisionWall = sm->second->getBoundary().top;
                    }
                    tempMap.insert({ std::make_pair(sm->first.first,collisionWall),sm->second });
                }
                secondMap->erase(sm);
            }
        }
        if (!tempMap.empty()) {
            for (auto t : tempMap) {
                secondMap->insert(t);
            }
        }
    }
    else {
        // <<oX,oY>, obj>
        if (!*secondAxis) {
            for (auto m : this->mapBlock) {
                //going through all blocks defined during initialization process:
                if ((m.second->getBoundary().top <= *rangeY->begin() && m.second->getBoundary().top + this->blockHight > *rangeY->begin()) ||
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
                if (m.first.second > *rangeY->rbegin()+ this->ballSize) break;
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
//void Game::colisionCheckPhase2(Ball* ball, std::set<float>* rangeX, std::set<float>* rangeY, std::multimap<std::pair<float, float>, Block*>* secondMap) {
float Game::colisionCheckPhase2(Ball * ball, float endPositionX, float endPositionY, std::multimap<std::pair<float, float>, Block*>*secondMap, std::set<float>* rangeX, std::set<float>* rangeY) {

    std::map <float, Block*> collisionMap{};

    float offsetX{ ((ball->getBallAlfa() < 90.) || (ball->getBallAlfa() > 270.) ? 1 : -1) * ball->getBallRadius() };
    float offsetY{ ((ball->getBallAlfa() <= 180.) ? -1 : 1) * ball->getBallRadius() };

    //check Y for collision with paddle:
    //PaddleY
    if (this->paddle->getBoundary().top <= *rangeY->rbegin()) {
        if (this->paddle->getBoundary().left <= *rangeX->begin() + ball->getBallRadius() && this->paddle->getBoundary().left + this->paddle->getBoundary().width >= *rangeX->rbegin() - ball->getBallRadius()) {
            float collisionX{ calculateCoords(
                       ball->getposition().x, ball->getposition().y + offsetY,
                       endPositionX, endPositionY + offsetY,
                       0, this->paddle->getBoundary().top ) };
            float distance{ calculateDistance(ball->getposition().x, ball->getposition().y + offsetY, collisionX, this->paddleLevel) };
            if (distance <= ball->getDistanceLeftToMove() + ball->getBallRadius() ) {
                collisionMap.insert({ distance, this->paddle });
            }
            std::cout << "Paddle" << std::endl;
        }
    }
    if (!secondMap->empty()) {
             // <<oX,oY>, obj>
            for (auto sm : *secondMap) {
                //Top Wall (-1, y) 
                //          -> need x value but use top ball pos (offsetY)
                //          -> ball is moving upwards
                //L/R Wall (x, -1) 
                //          -> need y value but use -x/x ball pos (offsetX)
                //          -> ball movieng side-side
                sm.second->setcolor(sf::Color::Yellow);////////

                float collisionX{ calculateCoords(
                    ball->getposition().x, ball->getposition().y + offsetY,
                    endPositionX, endPositionY + offsetY,
                    0, sm.first.second)};
                float distanceX{ calculateDistance(ball->getposition().x , ball->getposition().y + offsetY , collisionX, sm.first.second ) };
                if (distanceX <= ball->getDistanceLeftToMove()) {
                    std::cout << "[X]:" << distanceX;
                    collisionMap.insert({ distanceX, sm.second });
                }
                //calc y pos for know x value
                float collisionY{ calculateCoords(
                    ball->getposition().x + offsetX, ball->getposition().y,
                    endPositionX + offsetX, endPositionY ,
                    sm.first.first, 0) };
                float distanceY{ calculateDistance(ball->getposition().x+ offsetX , ball->getposition().y, sm.first.first, collisionY) };
                if (distanceY < ball->getDistanceLeftToMove()) {
                    std::cout << "[Y]:" << distanceY;
                    collisionMap.insert({ distanceY, sm.second });
                }
                std::cout << std::endl;
            }
            std::cout << "Y:" << collisionMap.size() << " " << ball->getDistanceLeftToMove();
            std::cout << "offset: x:" << offsetX << " y:" << offsetY;
            std::cout << std::endl;
    }
    if (!collisionMap.empty()) {
        //check if paddle will be hit
        for (auto c : collisionMap) {
            std::cout << c.first << ", ";
        }
        std::cout << std::endl;;
        collisionMap.begin()->second->setcolor(sf::Color::White);
        // ball->moveBall(collisionMap.begin()->first - ball->getSize());
        ball->changeDirection(180.);
        ball->ballGetStuck();
        return collisionMap.begin()->first;
    }
    return ball->getDistanceLeftToMove();
}
/*void Game::colisionCheckPaddle(Ball* ball) {
    //PaddleX
    if ((this->paddle->getBoundary().left <= *rangeX->rbegin() && this->paddle->getBoundary().left + this->paddle->getBoundary().width > *rangeX->begin()) ||
        (this->paddle->getBoundary().left > *rangeX->begin() && this->paddle->getBoundary().left < *rangeX->rbegin())) {
        secondMap->insert({ std::make_pair(this->paddle->getBoundary().left, 0.), this->paddle });
    }
    //PaddleY
    if ((this->paddle->getBoundary().top <= *rangeY->rbegin() && this->paddle->getBoundary().top + this->paddle->getBoundary().height > *rangeY->begin()) ||
        (this->paddle->getBoundary().top > *rangeY->begin() && this->paddle->getBoundary().top < *rangeY->rbegin())) {
        secondMap->insert({ std::make_pair(0., this->paddle->getBoundary().top), this->paddle });
    }
}
*/
float Game::calculateCoords(float startPositionX, float startPositionY, float endPositionX, float endPositionY, float collisionPositionX, float collisionPositionY){
    //return second coordinate (cx or cy)
    if (collisionPositionX == 0) return (startPositionX + (((collisionPositionY - startPositionY) * (endPositionX - startPositionX)) / (endPositionY - startPositionY)));
    if (collisionPositionY == 0) return (startPositionY + (((collisionPositionX - startPositionX) * (endPositionY - startPositionY)) / (endPositionX - startPositionX)));
}
float Game::calculateDistance(float x, float y, float a, float b) {
    return sqrt((x - a) * (x - a) + (y - b) * (y - b));
}
float Game::calculateDistanceX(float xp, float yp, float xs, float ys, float yc) {
    // Xc = Yc*X/Y 
    float xc_return = (yp-yc ) * ((xp - xs) / (yp - ys));
    return xc_return;
}
float Game::calculateDistanceY(float xp, float yp, float xs, float ys, float xc) {
    // Yc = Xc*Y/X
    float yc_return = (xp-xc) * ((ys - yp) / (xs - xp));
    return yc_return;
}
void Game::colisionAlgorithm(Ball* ball) {
    bool secondAxis{ false };
    std::multimap<std::pair<float, float>, Block*>* secondMap = new (std::multimap<std::pair<float, float>, Block*>);
    sf::Vector2f ballFirstPosition = ball->getposition();
    sf::Vector2f ballSecondPosition = ball->predictPosition();
    std::set<float> rangeX{ ballFirstPosition.x, ballSecondPosition.x };
    std::set<float> rangeY{ ballFirstPosition.y, ballSecondPosition.y };

    std::set<float> rangeXball{ *rangeX.begin() - ball->getBallRadius(), *rangeX.rbegin() + ball->getBallRadius() };
    std::set<float> rangeYball{ *rangeY.begin() - ball->getBallRadius(), *rangeY.rbegin() + ball->getBallRadius() };

    //sf::CircleShape p00, p01, p10, p11;
    //float r{ 5 };
    this->p00.setRadius(this->r);
    this->p01.setRadius(this->r);
    this->p10.setRadius(this->r);
    this->p11.setRadius(this->r);
    
    this->p00.setFillColor(sf::Color::Green);
    this->p01.setFillColor(sf::Color::Green);
    this->p10.setFillColor(sf::Color::Green);
    this->p11.setFillColor(sf::Color::Green);
    
    this->p00.setOrigin(this->r / 2, this->r / 2);
    this->p01.setOrigin(this->r / 2, this->r / 2);
    this->p10.setOrigin(this->r / 2, this->r / 2);
    this->p11.setOrigin(this->r / 2, this->r / 2);

    this->p00.setPosition(*rangeXball.begin(),  *rangeYball.begin());
    this->p01.setPosition(*rangeXball.begin(),  *rangeYball.rbegin());
    this->p10.setPosition(*rangeXball.rbegin(), *rangeYball.begin());
    this->p11.setPosition(*rangeXball.rbegin(), *rangeYball.rbegin());

    
    if (!ball->isBallStuck()) {
     //   std::cout << "S" << ball->getDistanceLeftToMove()<<"$" << std::endl;
        //if (*rangeX.rbegin() > 0 && *rangeY.rbegin() > 0) {
            if ((*rangeX.rbegin() - *rangeX.begin()) <= (*rangeY.rbegin() - *rangeY.begin())) {
                colisionCheckPhase1X(ball, &rangeXball, secondMap, &secondAxis);
                colisionCheckPhase1Y(ball, &rangeYball, secondMap, &secondAxis);
            }
            else {
                colisionCheckPhase1Y(ball, &rangeYball, secondMap, &secondAxis);
                colisionCheckPhase1X(ball, &rangeXball, secondMap, &secondAxis);
            }
            //if (!secondMap->empty()) colisionCheckPhase2(ball, &rangeX, &rangeY, secondMap);
            //if (!secondMap->empty()) 
            ball->moveBall(colisionCheckPhase2(ball, ballSecondPosition.x, ballSecondPosition.y, secondMap, &rangeXball, &rangeYball));
        //}
            //else ball->moveBall();
            std::cout << "Left to move:" << ball->getDistanceLeftToMove() << std::endl;
            if (ball->getDistanceLeftToMove() > 0.) colisionAlgorithm(ball);
        
    }
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
                int i = 0;
        }
    }
    window->draw(*paddle);
    for (Ball* ball : balls) {
        window->draw(*ball);
        ball->restoreMovement();
    }
    //window->draw(*this->mainFrame);

    window->draw(this->p00);
    window->draw(this->p01);
    window->draw(this->p10);
    window->draw(this->p11);

    window->display();
   //std::cout << "x:" << this->mainFrameCoords.x << " y:" << this->mainFrameCoords.y << " z:" << this->mainFrameCoords.z << std::endl;

}
