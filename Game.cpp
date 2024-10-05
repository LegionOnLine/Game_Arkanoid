#include "Game.h"



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

    std::vector <Block*> temp;
    temp.emplace_back(new Block(
        750,//1025,
        500,//500
        this->blockWidth,
        this->blockHight,
        1));
    this->blocks.push_back(temp);
    this->mapBlock.emplace(
        std::make_pair( temp.at(0)->getBoundary().left, 
            temp.at(0)->getBoundary().top),
        temp.at(0));

    /*
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
    */
  //  std::cout << "blockWidth: "<< this->blockWidth << std::endl;
    std::cout << "blocksSize:" << this->blocks.begin()->size() << std::endl;
}

void Game::initWindow(){
    this->window = new sf::RenderWindow(
        sf::VideoMode(this->windowWidth, this->windowHeight),
        "Arkanoid!",
        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(2);
    this->window->setVerticalSyncEnabled(false);

    this->mainFrameCoords.x = this->mainFrameWidth;
    this->mainFrameCoords.y = this->mainFrameWidth;
    this->mainFrameCoords.z = this->window->getSize().x * 0.9;

    this->mainFrameBottom = this->window->getSize().y - 100.;
    this->paddleLevel = this->mainFrameBottom;

    this->initMainFrame();
    //this->initBlocks(); //temporary block


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

void Game::pollEvent() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            this->window->close();
    }
    if (event.KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
            this->stop = false; //tmp
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
            window->clear();
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

void Game::colisionCheckPhase1X(Ball* ball, std::set<float>* rangeXball, std::set<Block*>* collisionSet) {
    std::set<Block*> tempSet{};
    if (collisionSet->empty()) {
        //collisionSet is empty - this is first axis verified
        for (auto m : this->mapBlock) {
            //going through all blocks defined during initialization process:
            if (*rangeXball->begin() <= m.second->getBoundary().left + m.second->getBoundary().width &&
                *rangeXball->rbegin() >= m.second->getBoundary().left) {
                collisionSet->insert(m.second);
            }
            if (m.first.first > *rangeXball->rbegin() + ball->getBallRadius()) break;
        }
    }
    else {
        // list of collision was not empty:
        for (auto colSet : *collisionSet) {
            if (*rangeXball->begin() <= colSet->getBoundary().left + colSet->getBoundary().width &&
                *rangeXball->rbegin() >= colSet->getBoundary().left) {
                tempSet.insert(colSet);
            }
        }
        collisionSet->clear();
        if (!tempSet.empty()) {
            for (auto t : tempSet) {
                collisionSet->insert(t);
            }
        }
    }
    ////LWall
    //if (this->leftWall->getBoundary().left + this->leftWall->getBoundary().width >= *rangeXball->begin() - ball->getBallRadius()) {
    //    collisionSet->insert(this->leftWall);
    //}
    ////RWall
    //if (this->rightWall->getBoundary().left <= *rangeXball->rbegin() + ball->getBallRadius()) {
    //    collisionSet->insert(this->rightWall);
    //}
}

void Game::colisionCheckPhase1Y(Ball* ball, std::set<float>* rangeYball, std::set<Block*>* collisionSet) {
    std::set<Block*> tempSet{};
    if (collisionSet->empty()) {
        //collisionSet is empty - this is first axis verified
        for (auto m : this->mapBlock) {
            //going through all blocks defined during initialization process:
            if (*rangeYball->begin() <= m.second->getBoundary().top + m.second->getBoundary().height &&
                *rangeYball->rbegin() >= m.second->getBoundary().top) {
                collisionSet->insert(m.second);
            }
            if (m.first.second > *rangeYball->rbegin() + ball->getBallRadius()) break;
        }
    }
    else {
        // list of collision was not empty:
        for (auto colSet : *collisionSet) {
            if (*rangeYball->begin() <= colSet->getBoundary().top + colSet->getBoundary().height &&
                *rangeYball->rbegin() >= colSet->getBoundary().top) {
                tempSet.insert(colSet);
            }
        }
        collisionSet->clear();
    }
    if (!tempSet.empty()) {
        for (auto t : tempSet) {
            collisionSet->insert(t);
        }
    }
    ////TopWall
    //if (this->topWall->getBoundary().height >= *rangeYball->begin() - ball->getBallRadius()) {
    //    collisionSet->insert(this->topWall);
    //}

}
void Game::colisionCheckPhase1Wall(Ball* ball, std::set<float>* rangeXball, std::set<float>* rangeYball, std::set<Block*>* collisionSet) {
    //TopWall
    if (this->topWall->getBoundary().top + this->topWall->getBoundary().height >= *rangeYball->begin() - ball->getBallRadius()) {
        collisionSet->insert(this->topWall);
        std::cout << "TOP";
    }
    //LWall
    if (this->leftWall->getBoundary().left + this->leftWall->getBoundary().width >= *rangeXball->begin() - ball->getBallRadius()) {
        collisionSet->insert(this->leftWall);
        std::cout << "Left";
    }
    //RWall
    if (this->rightWall->getBoundary().left <= *rangeXball->rbegin() + ball->getBallRadius()) {
        collisionSet->insert(this->rightWall);
        std::cout << "Right";
    }
}

float Game::colisionCheckPhase2(Ball* ball, sf::Vector2f ballEndPosition, std::set<Block*>* collisionSet, std::set<float>* rangeX, std::set<float>* rangeY) {
    std::multimap <float, std::pair<Block*, std::pair<sf::Vector2f, char> > > collisionMap{};
    float ballRadius{ ball->getBallRadius() };

    ////ball offset
    //float ballOffsetX{ ((ball->getBallDirection() & 0x10) ? 0 : 1) * ballRadius };
    //float ballOffsetY{ ((ball->getBallDirection() & 0x01) ? 1 : 0) * ballRadius };
    ////block offset
    //int blockOffsetX{ ((ball->getBallDirection() & 0x10) ? 0 : 1) };
    //int blockOffsetY{ ((ball->getBallDirection() & 0x01) ? 0 : 1) };

    float ballOffsetX{ ballRadius };
    float ballOffsetY{ ballRadius };
    int blockOffsetX{};
    int blockOffsetY{};
    if (ball->getBallDirection() == 0x00) { // Left - Up
        ballOffsetX *= -1.f;
        ballOffsetY *= -1.f;
        blockOffsetX = 1;
        blockOffsetY = 1;
    }
    else if (ball->getBallDirection() == 0x01) { // Left - Down
        ballOffsetX *= -1.f;
        ballOffsetY *= 1.f;
        blockOffsetX = 1;
        blockOffsetY = 0;
    }
    else if (ball->getBallDirection() == 0x10) { // Right - Up
        ballOffsetX *= 1.f;
        ballOffsetY *= -1.f;
        blockOffsetX = 0;
        blockOffsetY = 1;
    }
    else {                                         //Right - Down
        ballOffsetX *= 1.f;
        ballOffsetY *= 1.f;
        blockOffsetX = 0;
        blockOffsetY = 0;
    }
    //ballOffsetX *= ballRadius;
    //ballOffsetY *= ballRadius;

    //check Y for collision with paddle:
    //PaddleY
    if (this->paddle->getBoundary().top <= *rangeY->rbegin()) {
        if (this->paddle->getBoundary().left <= *rangeX->begin() + ballRadius && this->paddle->getBoundary().left + this->paddle->getBoundary().width >= *rangeX->rbegin() - ballRadius) {
            float collisionX{ calculateCoords(
                       ball->getposition().x, ball->getposition().y + ballOffsetY,
                       ballEndPosition.x, ballEndPosition.y + ballOffsetY,
                       0, this->paddle->getBoundary().top) };
            float distance{ calculateDistance(ball->getposition().x, ball->getposition().y + ballOffsetY, collisionX, this->paddleLevel) };
            if (distance <= ball->getDistanceLeftToMove() + ballRadius) {
                collisionMap.insert({ distance, std::make_pair(this->paddle, std::make_pair(sf::Vector2f{collisionX,this->paddle->getBoundary().top} ,'y')) });
            }
        }
    }
    //possible collision with any block since it exist in collisionSet 
    if (!collisionSet->empty()) {
        for (auto object : *collisionSet) {
            object->setcolor(sf::Color::Yellow);

            // For each object we need to calculate 2 collison points:
            //     collisionX - collision point in X-axis, y taken from block wall
            //     collisionY - collision point in Y-axis, x taken from block wall
            // 0 is for function to know what value we want to find
            std::cout << "colisionSet is not empty!" << std::endl;

            //  ballOffsetX
            //  ballOffsetY
            //  blockOffsetX
            //  blockOffsetY
            //vvvvvv TO BE DONE VVVVVVVVVVVVV
            //Original:
            //float blockWallX{ object->getBoundary().left + blockOffsetX * object->getBoundary().width };
            //float blockWallY{ object->getBoundary().top + blockOffsetY * object->getBoundary().height };
            //
            //float collisionX{ calculateCoords(
            //    ball->getposition().x, ball->getposition().y + ballOffsetY,         // ball start point
            //    ballEndPosition.x, ballEndPosition.y + ballOffsetY,                 // ball end point
            //    0, blockWallY) };                                                    // block wall
            //float collisionY{ calculateCoords(
            //    ball->getposition().x + ballOffsetX, ball->getposition().y,         // ball start point
            //    ballEndPosition.x + ballOffsetX, ballEndPosition.y,                 // ball end point
            //    blockWallX, 0) };

            //Instead of calculating ball dimention each time, just change collision wall by ball dimention :?
            //if this will work I need to change sign above to realy add or substract instead of substracting minus value
            float blockWallX{ object->getBoundary().left + blockOffsetX * object->getBoundary().width - ballOffsetX };
            float blockWallY{ object->getBoundary().top + blockOffsetY * object->getBoundary().height - ballOffsetY };

            float collisionX{ calculateCoords(
                ball->getposition(),            // ball start point
                ballEndPosition,                // ball end point
                0, blockWallY)};                // block wall
            float collisionY{ calculateCoords(
                ball->getposition(),            // ball start point
                ballEndPosition,                // ball end point
                blockWallX, 0)};                // block wall

            // float Game::calculateDistance(float x, float y, float a, float b) {
            // return sqrt((x - a) * (x - a) + (y - b) * (y - b));

            // check if collision point is in direction of ball movement

            // // //ball offset
            // // float ballOffsetX{ ((ball->getBallDirection() & 0x10) ? 0 : 1) * ballRadius };
            // // float ballOffsetY{ ((ball->getBallDirection() & 0x01) ? 1 : 0) * ballRadius };
            // // //block offset
            // // int blockOffsetX{ ((ball->getBallDirection() & 0x10) ? 0 : 1) };
            // // int blockOffsetY{ ((ball->getBallDirection() & 0x01) ? 0 : 1) };
            float distanceX{-1.f};
            float distanceY{-1.f};
            //if moving collision point by ball radious it is not needed to use ballOffset anymore
            //if ((ball->getBallDirection() & 0x10)) {   //going right
            //    if (collisionX > ball->getposition().x) {
            //        distanceX = calculateDistance(ball->getposition().x, ball->getposition().y + ballOffsetY,
            //                        collisionX, blockWallY);
            //        distanceY = calculateDistance(ball->getposition().x + ballOffsetX, ball->getposition().y,
            //                        blockWallX, collisionY) ;
            //    }
            //}
            //else {
            //    if (collisionX < ball->getposition().x) {
            //        distanceX = calculateDistance(ball->getposition().x, ball->getposition().y + ballOffsetY,
            //            collisionX, blockWallY);
            //        distanceY = calculateDistance(ball->getposition().x + ballOffsetX, ball->getposition().y,
            //            blockWallX, collisionY);
            //    }
            //}

            //if ((ball->getBallDirection() & 0x10)) {   //going right
            //    std::cout << std::endl << "ball going right" << std::endl;
            //    // collisionX - for know y lvl find collision point in x axis
            //    if (collisionX > ball->getposition().x) { //colision is to the right of current position
            //
            //        std::cout <<  "ball if - if" << std::endl;
            //        distanceX = calculateDistance(ball->getposition().x, ball->getposition().y,
            //            collisionX, blockWallY);
            //        distanceY = calculateDistance(ball->getposition().x, ball->getposition().y,
            //            blockWallX, collisionY);
            //    }
            //}
            //else {          //going left
            //    std::cout << std::endl << "ball going left" << std::endl;
            //    if (collisionX < ball->getposition().x) { // collision is to th eleft of current position
            //        distanceX = calculateDistance(ball->getposition().x, ball->getposition().y,
            //            collisionX, blockWallY);
            //        distanceY = calculateDistance(ball->getposition().x, ball->getposition().y,
            //            blockWallX, collisionY);
            //    }
            //}
            //
            //bool flag{ false };

            if ((ball->getBallDirection() & 0x10)) { //going right 
                if (collisionX > ball->getposition().x) { //collision is to the right
                    distanceX = calculateDistance(ball->getposition(), collisionX, blockWallY);
                }
            }
            else { //going left
                if (collisionX < ball->getposition().x) { //collision is to the left
                    distanceX = calculateDistance(ball->getposition(), collisionX, blockWallY);
                }
            }
            if ((ball->getBallDirection() & 0x01)) { // going donw
                if (collisionY > ball->getposition().y) { // collision is lower (higher y value)
                    distanceY = calculateDistance(ball->getposition(), blockWallX, collisionY);
                }
            }
            else { // going up
                if (collisionY < ball->getposition().y) { // collision is higher (lower y value)
                    distanceY = calculateDistance(ball->getposition(), blockWallX, collisionY);
                }
            }

            //if (flag) {
            //    std::cout << std::endl << "flag is true" << std::endl;
            //    distanceX = calculateDistance(ball->getposition().x, ball->getposition().y,
            //        collisionX, blockWallY);
            //    distanceY = calculateDistance(ball->getposition().x, ball->getposition().y,
            //        blockWallX, collisionY);
            //
            //}


            std::cout << std::endl << "DistanceX - " << distanceX << std::endl << "DistanceY - " << distanceY << std::endl;
            // distanceX and distanceY is calculated from ball position +/- offset in specific direction
            // if collision is within R range from block corner then it is cornercase



            //if (distanceX <= ball->getDistanceLeftToMove() && distanceY <= ball->getDistanceLeftToMove()) {
            //    std::cout << "conrercase!!! ???";
            //}
            if (distanceX > 0.f) {
                if (distanceX <= ball->getDistanceLeftToMove()) {
                    std::cout << "X!!! ";
                    //collisionMap.insert({ distanceX , sm.second });
                    collisionMap.insert({ distanceX, std::make_pair(object, std::make_pair(sf::Vector2f{collisionX,blockWallY}, 'y')) });
                    // });
                }
            }
            if (distanceY > 0.f) {
                if (distanceY <= ball->getDistanceLeftToMove()) {
                    std::cout << "Y!!! ";
                    //collisionMap.insert({ distanceY , sm.second });
                    collisionMap.insert({ distanceY, std::make_pair(object, std::make_pair(sf::Vector2f{blockWallX, collisionY}, 'x')) });
                    // });
                }
            }
        }
    }
    if (!collisionMap.empty()) {
        //std::cout << "collisionMap: ";
        //for (auto c : collisionMap) {
        //    std::cout << "Id:" << c.second.first->getId() << " dist: ";
        //    std::cout << c.first << ", ";
        //}
        //std::cout << "/" << ball->getDistanceLeftToMove() << std::endl;

        collisionMap.begin()->second.first->setcolor(sf::Color::White);
        //if distance is > ball dimention then move ball by distane - R
        //if distance is < ball dimention then move ball by 1. (?)

        // std::multimap <float, std::pair<
        //                                 Block*, std::pair<
        //                                                   sf::Vector2f, char> > > collisionMap{};
        ball->moveBall(collisionMap.begin()->first - ballRadius);//75.f);
        //ball->moveBall(collisionMap.begin()->first - 5);
        for (float i{ ballRadius }; i > 0; i--) {
            //std::cout << "collision point() ("
            //    << collisionMap.begin()->second.second.first.x << " | "
            //    << collisionMap.begin()->second.second.first.y << ") ball current possition [ "
            //    << ball->getposition().x << " | "
            //    << ball->getposition().y << "]"
            //    << std::endl;

            //ball->predictPosition(1.f);
            //ball->moveBall(1.f);
            //if (calculateDistance(ball->getposition(), ball->predictPosition(1.f)) <= 1.f) {
            if (calculateDistance(ball->getposition(), collisionMap.begin()->second.second.first ) <= 1.f) {

                std::cout << "HIT??? distance left to move =" << ball->getDistanceLeftToMove() << std::endl;
                std::cout << "distance to colliding point: " << calculateDistance(ball->getposition(), collisionMap.begin()->second.second.first) - ballRadius << std::endl;

                //check if point is part of block
                char normalAxis{ collisionMap.begin()->second.second.second };


                //std::cout << "alpha angel:" << ball->getBallAlfa();
                ball->changeDirection(collisionRespond(ball->getBallAlfa(), normalAxis));
                //std::cout << " -> new angle: " << ball->getBallAlfa() << std::endl;
                ball->ballGetStuck();

                std::cout << "====================" << std::endl;
                break;
                return 0;
            }
            else {
                std::cout << "<";
                ball->moveBall(1.f);
            }

        }
        std::cout << "--------------------" << std::endl;
        std::cout << "exiting for loop" << std::endl;
        return 0;
        return ball->getDistanceLeftToMove();
    }
    std::cout << "+FreeMove+" << std::endl;
    ball->moveBall(ball->getDistanceLeftToMove());
    return ball->getDistanceLeftToMove();




}

float Game::collisionRespond(float alpha, char normalAxis){
    //std::cout <<"("<< normalAxis << ")";
    if (alpha < 90.f) {
        if (normalAxis == 'x') return 2 * (90.f - alpha);//360.f - 2*alpha;
        if (normalAxis == 'y') return -2 * alpha;//180.f - 2*alpha;
    }
    if (alpha < 180.f) {
        if (normalAxis == 'x') return -2 * (alpha - 90.f); //180.f - 2*alpha; //-(180.f - 2*(180.f - alpha));
        if (normalAxis == 'y') return 2 * (180.f - alpha); //360.f - 2*alpha ;
    }
    if (alpha < 270.f) {
        if (normalAxis == 'x') return 2 * (270.f - alpha);//2*alpha - 360.f;
        if (normalAxis == 'y') return -2 * (alpha - 180.f);//360.f - 2*alpha; //alpha - 180.f;
    }
    if (normalAxis == 'x') return -2 * (alpha - 270.f);//180.f + 2*(360.f - alpha);
    if (normalAxis == 'y') return 2 * (360.f - alpha);//2*(360.f - alpha);
    
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
float Game::calculateCoords(sf::Vector2f startPosition, sf::Vector2f endPosition, float collisionPositionX, float collisionPositionY) {
    //return second coordinate (cx or cy)
    if (collisionPositionX == 0) return (startPosition.x + (((collisionPositionY - startPosition.y) * (endPosition.x - startPosition.x)) / (endPosition.y - startPosition.y)));
    if (collisionPositionY == 0) return (startPosition.y + (((collisionPositionX - startPosition.x) * (endPosition.y - startPosition.y)) / (endPosition.x - startPosition.x)));

}
float Game::calculateDistance(sf::Vector2f ballPos, sf::Vector2f colision) {
    return sqrt((ballPos.x - colision.x) * (ballPos.x - colision.x) + (ballPos.y - colision.y) * (ballPos.y - colision.y));
}
float Game::calculateDistance(sf::Vector2f ball, float colisionX, float colisionY) {
    return sqrt((ball.x - colisionX) * (ball.x - colisionX) + (ball.y - colisionY) * (ball.y - colisionY));
}
float Game::calculateDistance(float ballX, float ballY, float colisionX, float colisionY) {
    return sqrt((ballX - colisionX) * (ballX - colisionX) + (ballY - colisionY) * (ballY - colisionY));
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
    std::set<Block*>* collisionSet = new (std::set<Block*>);
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

                    this->v0 = sf::Vertex(sf::Vector2f(*rangeXball.begin(), *rangeYball.begin()));
                    this->v1 = sf::Vertex(sf::Vector2f(*rangeXball.begin(), *rangeYball.rbegin()));
                    this->v2 = sf::Vertex(sf::Vector2f(*rangeXball.rbegin(), *rangeYball.rbegin()));
                    this->v3 = sf::Vertex(sf::Vector2f(*rangeXball.rbegin(), *rangeYball.begin()));

    if (!ball->isBallStuck()) {//} && !this->stop) {
     //   std::cout << "S" << ball->getDistanceLeftToMove()<<"$" << std::endl;
        //if (*rangeX.rbegin() > 0 && *rangeY.rbegin() > 0) {
            //if ((*rangeX.rbegin() - *rangeX.begin()) <= (*rangeY.rbegin() - *rangeY.begin())) {
        //Using Set
        colisionCheckPhase1X(ball, &rangeXball, collisionSet);
        colisionCheckPhase1Y(ball, &rangeYball, collisionSet);
        colisionCheckPhase1Wall(ball, &rangeXball, &rangeYball, collisionSet);
            //}
            //else {
            //    colisionCheckPhase1Y(ball, &rangeYball, secondMap, &secondAxis);
            //    colisionCheckPhase1X(ball, &rangeXball, secondMap, &secondAxis);
            //}
            //if (!secondMap->empty()) colisionCheckPhase2(ball, &rangeX, &rangeY, secondMap);
            //if (!secondMap->empty()) 
            //ball->moveBall(colisionCheckPhase2(ball, ballSecondPosition.x, ballSecondPosition.y, secondMap, &rangeXball, &rangeYball));

            //colisionCheckPhase2(ball, ballSecondPosition.x, ballSecondPosition.y, secondMap, &rangeXball, &rangeYball);
        colisionCheckPhase2(ball, ballSecondPosition, collisionSet, &rangeX, &rangeY);
            //ball->ballGetStuck();
        //}
            //else ball->moveBall();
            //std::cout << "Left to move:" << ball->getDistanceLeftToMove() << std::endl;
           // ball->ballGetStuck();
        
    }
    delete collisionSet;
    //if (ball->getDistanceLeftToMove() > 0. && !ball->isBallStuck()) colisionAlgorithm(ball);

    //this->stop = true;
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
            while (ball->getDistanceLeftToMove() > 0. && !ball->isBallStuck()) {
                colisionAlgorithm(ball);
            }

           // if (intersection(ball, counter)) ballLost = true;  //counter can be discarded
            //counter++;
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

    sf::Vertex line[5] = {
        this->v0,
        this->v1,
        this->v2,
        this->v3,
        this->v0
    };
    this->window->draw(line, 5, sf::LineStrip);

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
