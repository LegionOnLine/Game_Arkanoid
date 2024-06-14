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

void Game::colisionCheckPhase1X(Ball* ball, std::set<float>* rangeX, std::set<Block*>* collisionSet) {
    std::set<Block*> tempSet{};
    if (collisionSet->empty()) {
        //collisionSet is empty - this is first axis verified
        for (auto m : this->mapBlock) {
            //going through all blocks defined during initialization process:
            if (*rangeX->begin() <= m.second->getBoundary().left + m.second->getBoundary().width &&
                *rangeX->rbegin() >= m.second->getBoundary().left) {
                collisionSet->insert(m.second);
            }
            if (m.first.first > *rangeX->rbegin() + ball->getBallRadius()) break;
        }
    }
    else {
        // list of collision was not empty:
        for (auto colSet : *collisionSet) {
            if (*rangeX->begin() <= colSet->getBoundary().left + colSet->getBoundary().width &&
                *rangeX->rbegin() >= colSet->getBoundary().left) {
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
    //LWall
    if (this->leftWall->getBoundary().left + this->leftWall->getBoundary().width >= *rangeX->begin() - ball->getBallRadius()) {
        collisionSet->insert(this->leftWall);
    }
    //RWall
    if (this->rightWall->getBoundary().left <= *rangeX->rbegin() + ball->getBallRadius()) {
        collisionSet->insert(this->rightWall);
    }
}
void Game::colisionCheckPhase1X(Ball *ball, std::set<float>* rangeX, std::multimap<std::pair<float, float>, Block*> *secondMap, bool* secondAxis){
    if (!secondMap->empty()) { //list is not empty
        std::multimap<std::pair<float, float>, Block*> tempMap{};
        for (auto sm{secondMap->cbegin()}, nsm{sm}; sm != secondMap->cend(); sm = nsm) {
            nsm++;
            if (sm->first.first == 0.) {
                if (*rangeX->begin() <= sm->second->getBoundary().left + sm->second->getBoundary().width &&
                    *rangeX->rbegin() >= sm->second->getBoundary().left){
                    //overcomplicated if
                //if ((sm->second->getBoundary().left < *rangeX->begin() && sm->second->getBoundary().left + sm->second->getBoundary().width >= *rangeX->begin()) ||
                //    (sm->second->getBoundary().left >= *rangeX->begin() && sm->second->getBoundary().left <= *rangeX->rbegin())) {
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
                if (*rangeX->begin() <= m.second->getBoundary().left + m.second->getBoundary().width &&
                    *rangeX->rbegin() >= m.second->getBoundary().left) {
                    //overcomplicated if
               // if ((m.second->getBoundary().left <= *rangeX->begin() && m.second->getBoundary().left + m.second->getBoundary().width > *rangeX->begin()) ||
               //     (m.second->getBoundary().left > *rangeX->begin() && m.second->getBoundary().left < *rangeX->rbegin())) {

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

void Game::colisionCheckPhase1Y(Ball* ball, std::set<float>* rangeY, std::set<Block*>* collisionSet) {
    std::set<Block*> tempSet{};
    if (collisionSet->empty()) {
        //collisionSet is empty - this is first axis verified
        for (auto m : this->mapBlock) {
            //going through all blocks defined during initialization process:
            if (*rangeY->begin() <= m.second->getBoundary().top + m.second->getBoundary().height &&
                *rangeY->rbegin() >= m.second->getBoundary().top) {
                collisionSet->insert(m.second);
            }
            if (m.first.second > *rangeY->rbegin() + ball->getBallRadius()) break;
        }
    }
    else {
        // list of collision was not empty:
        for (auto colSet : *collisionSet) {
            if (*rangeY->begin() <= colSet->getBoundary().top + colSet->getBoundary().height &&
                *rangeY->rbegin() >= colSet->getBoundary().top) {
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
    //TopWall
    if (this->topWall->getBoundary().height >= *rangeY->begin() - ball->getBallRadius()) {
        collisionSet->insert(this->topWall);
    }

}
    

void Game::colisionCheckPhase1Y(Ball* ball, std::set<float>* rangeY, std::multimap<std::pair<float, float>, Block*>* secondMap, bool* secondAxis) {
    //if it's new list use 0 in x-coords, -1 is reserved for walls etc.
    if (!secondMap->empty()) { //list is not empty
        std::multimap<std::pair<float, float>, Block*> tempMap{};
        for (auto sm{ secondMap->cbegin() }, nsm{ sm }; sm != secondMap->cend(); sm = nsm) {
            nsm++;
            if (sm->first.second == 0.) {
                if (*rangeY->begin() <= sm->second->getBoundary().top + sm->second->getBoundary().height &&
                    *rangeY->rbegin() >= sm->second->getBoundary().top) {
                //overcomplicated if
                //if ((sm->second->getBoundary().top < *rangeY->begin() && sm->second->getBoundary().top + sm->second->getBoundary().height >= *rangeY->begin()) ||
                //    (sm->second->getBoundary().top >= *rangeY->begin() && sm->second->getBoundary().top <= *rangeY->rbegin())) {
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
                if (*rangeY->begin() <= m.second->getBoundary().top + m.second->getBoundary().height &&
                    *rangeY->rbegin() >= m.second->getBoundary().top) {
                    //overcomplicated if
                //if ((m.second->getBoundary().top <= *rangeY->begin() && m.second->getBoundary().top + this->blockHight > *rangeY->begin()) ||
                //    (m.second->getBoundary().top > *rangeY->begin() && m.second->getBoundary().top < *rangeY->rbegin())) {
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

float Game::colisionCheckPhase2(Ball* ball, float endPositionX, float endPositionY, std::set<Block*>* collisionSet, std::set<float>* rangeX, std::set<float>* rangeY) {
    std::multimap <float, std::pair<Block*, std::pair<sf::Vector2f, char> > > collisionMap{};
    float ballRadius{ ball->getBallRadius() };
    //ball offset
    float ballOffsetX{ ((ball->getBallDirection() & 0x10) ? 0 : 1) * ballRadius };
    float ballOffsetY{ ((ball->getBallDirection() & 0x01) ? 1 : 0) * ballRadius };
    //block offset
    int blockOffsetX{ ((ball->getBallDirection() & 0x10) ? 0 : 1) };
    int blockOffsetY{ ((ball->getBallDirection() & 0x01) ? 0 : 1) };

    //check Y for collision with paddle:
    //PaddleY
    if (this->paddle->getBoundary().top <= *rangeY->rbegin()) {
        if (this->paddle->getBoundary().left <= *rangeX->begin() + ballRadius && this->paddle->getBoundary().left + this->paddle->getBoundary().width >= *rangeX->rbegin() - ballRadius) {
            float collisionX{ calculateCoords(
                       ball->getposition().x, ball->getposition().y + ballOffsetY,
                       endPositionX, endPositionY + ballOffsetY,
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


            //  ballOffsetX
            //  ballOffsetY
            //  blockOffsetX
            //  blockOffsetY
            //vvvvvv TO BE DONE VVVVVVVVVVVVV
            float blockWallX{ object->getBoundary().left + blockOffsetX * object->getBoundary().width };
            float blockWallY{ object->getBoundary().top + blockOffsetY * object->getBoundary().height };


            float collisionX{ calculateCoords(
                ball->getposition().x, ball->getposition().y + ballOffsetY,                         // ball start point
                endPositionX, endPositionY + ballOffsetY,                                           // ball end point
                0, blockWallY)};         // block wall
            float collisionY{ calculateCoords(
                ball->getposition().x + ballOffsetX, ball->getposition().y,                         // ball start point
                endPositionX + ballOffsetX, endPositionY,                                           // ball end point
                blockWallX, 0)};         // block wall

            // float Game::calculateDistance(float x, float y, float a, float b) {
            // return sqrt((x - a) * (x - a) + (y - b) * (y - b));
            float distanceX{ calculateDistance(ball->getposition().x, ball->getposition().y + ballOffsetY,
                            collisionX, blockWallY) };
            float distanceY{ calculateDistance(ball->getposition().x + ballOffsetX, ball->getposition().y,
                            blockWallX, collisionY) };
            // distanceX and distanceY is calculated from ball position +/- offset in specific direction

            // if collision is within R range from block corner then it is cornercase



            if (distanceX <= ball->getDistanceLeftToMove() && distanceY <= ball->getDistanceLeftToMove()) {
                std::cout << "conrercase!!! ???";
            }
            if (distanceX <= ball->getDistanceLeftToMove()) {
                std::cout << "X!!! ";
                //collisionMap.insert({ distanceX , sm.second });
                collisionMap.insert({ distanceX, std::make_pair(object, std::make_pair(sf::Vector2f{collisionX,blockWallY}, 'y')) });
                // });
            }
            if (distanceY <= ball->getDistanceLeftToMove()) {
                std::cout << "Y!!! ";
                //collisionMap.insert({ distanceY , sm.second });
                collisionMap.insert({ distanceY, std::make_pair(object, std::make_pair(sf::Vector2f{blockWallX, collisionY}, 'x')) });
                // });
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
            if (calculateDistance(ball->getposition(), ball->predictPosition(1.f)) <= 1.f) {

                std::cout << "HIT??? distance left to move =" << ball->getDistanceLeftToMove() << std::endl;
                std::cout << "distance to colliding point: " << calculateDistance(ball->getposition(), collisionMap.begin()->second.second.first) - ballRadius << std::endl;

                //check if point is part of block
                char normalAxis{ collisionMap.begin()->second.second.second };


                //std::cout << "alpha angel:" << ball->getBallAlfa();
                ball->changeDirection(collisionRespond(ball->getBallAlfa(), normalAxis));
                //std::cout << " -> new angle: " << ball->getBallAlfa() << std::endl;
                ball->ballGetStuck();

                std::cout << "====================" << std::endl;
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
    std::cout << "++++++++++++++++++++++" << std::endl;
    ball->moveBall(ball->getDistanceLeftToMove());
    return ball->getDistanceLeftToMove();




}
//void Game::colisionCheckPhase2(Ball* ball, std::set<float>* rangeX, std::set<float>* rangeY, std::multimap<std::pair<float, float>, Block*>* secondMap) {
float Game::colisionCheckPhase2(Ball* ball, float endPositionX, float endPositionY, std::multimap<std::pair<float, float>, Block*>*secondMap, std::set<float>* rangeX, std::set<float>* rangeY) {

    // From colisionCheckPhase1 we have list of potential coliding objects. 
    // Object will be on the list if it will be within ball movement range in X- and Y-axis.
    // Now it is necessary to check if collision will occur in top/bottom or left/right point of ball or will it be corner-case.
    // 

    //std::multimap <float, Block* > collisionMap{};
    //std::multimap <float, std::pair<Block*, sf::Vector3f> > collisionMap{};
    std::multimap <float, std::pair<Block*, std::pair<sf::Vector2f,char> > > collisionMap{};
    float ballRadius{ ball->getBallRadius() };
    float offsetX{ ((ball->getBallAlfa() < 90.) || (ball->getBallAlfa() > 270.) ? 1 : -1) * ballRadius };
    float offsetY{ ((ball->getBallAlfa() <= 180.) ? -1 : 1)* ballRadius};
    int d = ball->getBallAlfa() / 90.f +1;
    std::cout << "<<<" << ball->getBallAlfa() << " - " <<  d << ball->getBallDirection()<< ">>>" << std::endl;
    std::cout << "Masks output for ball direction (" << ball->getBallDirection() << "):" << std::endl
        << "0x00 = " << (ball->getBallDirection() & 0x00) << std::endl
        << "0x01 = " << (ball->getBallDirection() & 0x01) << std::endl
        << "0x10 = " << (ball->getBallDirection() & 0x10) << std::endl
        << "0x11 = " << (ball->getBallDirection() & 0x11) << std::endl;
    //if (ball->getBallDirection() & 0x02) std::cout << "Mask True - going left" << (ball->getBallDirection() & 0x02) << std::endl;
    //else std::cout << "Mask True - going right" << (ball->getBallDirection() & 0x02) << std::endl;
    //if (ball->getBallDirection()>>1 & 0x02) std::cout << "Mask True - going up" << (ball->getBallDirection()>>1 & 0x02) << std::endl;
    //else std::cout << "Mask True - going down" << (ball->getBallDirection() >> 1 & 0x02) << std::endl;

    //check Y for collision with paddle:
    //PaddleY
    if (this->paddle->getBoundary().top <= *rangeY->rbegin()) {
        if (this->paddle->getBoundary().left <= *rangeX->begin() + ballRadius && this->paddle->getBoundary().left + this->paddle->getBoundary().width >= *rangeX->rbegin() - ballRadius) {
            float collisionX{ calculateCoords(
                       ball->getposition().x, ball->getposition().y + offsetY,
                       endPositionX, endPositionY + offsetY,
                       0, this->paddle->getBoundary().top ) };
            float distance{ calculateDistance(ball->getposition().x, ball->getposition().y + offsetY, collisionX, this->paddleLevel) };
            if (distance <= ball->getDistanceLeftToMove() + ballRadius) {
                //collisionMap.insert({ distance, this->paddle });
                collisionMap.insert({ distance, std::make_pair(this->paddle, std::make_pair(sf::Vector2f{collisionX,this->paddle->getBoundary().top} ,'y')) });
            }
            //std::cout << "Paddle" << std::endl;
        }
    }
    //possible collision with any block since it is in secondMap 
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
                
                // knowing wall we will colide with we needs to calculate collision point to have (x,y) 
                // collisionX - collision point in X-axis, y taken from block wall
                // collisionY - collision point in Y-axis, x taken from block wall

                float collisionX{ calculateCoords(
                    ball->getposition().x, ball->getposition().y + offsetY,
                    endPositionX, endPositionY + offsetY,
                    0, sm.first.second)}; //point where ball will hit. 0 is looking value
                float collisionY{ calculateCoords(
                    ball->getposition().x + offsetX, ball->getposition().y,
                    endPositionX + offsetX, endPositionY ,
                    sm.first.first, 0) };

               
                // float Game::calculateDistance(float x, float y, float a, float b) {
                // return sqrt((x - a) * (x - a) + (y - b) * (y - b));
                float distanceX{ calculateDistance(ball->getposition().x , ball->getposition().y + offsetY , collisionX, sm.first.second) };
                float distanceY{ calculateDistance(ball->getposition().x + offsetX , ball->getposition().y, sm.first.first, collisionY) };
                // distanceX and distanceY is calculated from ball position +/- offset in specific direction
                    
                // if collision is within R range from block corner then it is cornercase



                    if (distanceX <= ball->getDistanceLeftToMove() && distanceY <= ball->getDistanceLeftToMove()) {
                        std::cout << "conrercase!!! ???" ;
                    }
                    if (distanceX <= ball->getDistanceLeftToMove()) {
                        std::cout << "X!!! " ;
                        //collisionMap.insert({ distanceX , sm.second });
                        collisionMap.insert({ distanceX, std::make_pair(sm.second, std::make_pair(sf::Vector2f{collisionX,sm.first.second}, 'y')) });
                   // });
                    }
                    if (distanceY <= ball->getDistanceLeftToMove()) {
                        std::cout << "Y!!! ";
                        //collisionMap.insert({ distanceY , sm.second });
                        collisionMap.insert({ distanceY, std::make_pair(sm.second, std::make_pair(sf::Vector2f{sm.first.first, collisionY}, 'x')) });
                   // });
                    }
            }
    }
    if (!collisionMap.empty()) {
        std::cout << "collisionMap: ";
        for (auto c : collisionMap) {
            std::cout << "Id:" << c.second.first->getId() << " dist: ";
            std::cout << c.first << ", ";
        }
        std::cout << "/" <<  ball->getDistanceLeftToMove() << std::endl;

        collisionMap.begin()->second.first->setcolor(sf::Color::White);
        //if distance is > ball dimention then move ball by distane - R
        //if distance is < ball dimention then move ball by 1. (?)

        // std::multimap <float, std::pair<
        //                                 Block*, std::pair<
        //                                                   sf::Vector2f, char> > > collisionMap{};
        ball->moveBall(collisionMap.begin()->first - ballRadius);//75.f);
        //ball->moveBall(collisionMap.begin()->first - 5);
        for (float i{ ballRadius }; i > 0; i--) {
            std::cout << "collision point() ("
                << collisionMap.begin()->second.second.first.x << " | "
                << collisionMap.begin()->second.second.first.y << ") ball current possition [ " 
                << ball->getposition().x << " | "
                << ball->getposition().y << "]" 
                << std::endl;

            //ball->predictPosition(1.f);
            //ball->moveBall(1.f);
            if (calculateDistance(ball->getposition(), ball->predictPosition(1.f)) <= ballRadius) {
                
                std::cout << "HIT??? distance left to move =" << ball->getDistanceLeftToMove() << std::endl;
                std::cout << "distance to colliding point: " << calculateDistance(ball->getposition(), collisionMap.begin()->second.second.first) - ballRadius << std::endl;

                //check if point is part of block
                char normalAxis{ collisionMap.begin()->second.second.second };


                std::cout << "alpha angel:" << ball->getBallAlfa();
                ball->changeDirection(collisionRespond(ball->getBallAlfa(), normalAxis));
                std::cout << " -> new angle: " << ball->getBallAlfa() << std::endl;
                ball->ballGetStuck();

                std::cout << "====================" << std::endl;
                return 0;
            }
            else {
                std::cout << "<";
                ball->moveBall(1.f);
            }

            //ball->predictPosition(1.f);
            //ball->moveBall(1.f);
            //if (calculateDistance(ball->getposition().x, ball->getposition().y, collisionMap.begin()->second.second.first.x, collisionMap.begin()->second.second.first.y) <= ballRadius) {
            //    std::cout << "HIT???-" << ball->getDistanceLeftToMove() <<  std::endl;
            //    //check if point is part of block
            //    char normalAxis{ collisionMap.begin()->second.second.second };
            //    
            //    
            //    std::cout << "alpha:" << ball->getBallAlfa();
            //    ball->changeDirection(collisionRespond(ball->getBallAlfa(), normalAxis));
            //    std::cout << " - " << ball->getBallAlfa() << std::endl;
            //    //ball->ballGetStuck();
            //    return 0;
            //}
        }
        std::cout << "--------------------" << std::endl;
        std::cout << "exiting for loop" << std::endl;
        return 0;
        return ball->getDistanceLeftToMove();
    }
    std::cout << "++++++++++++++++++++++" << std::endl;
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
float Game::calculateDistance(sf::Vector2f ballPos, sf::Vector2f colision) {
    return sqrt((ballPos.x - colision.x) * (ballPos.x - colision.x) + (ballPos.y - colision.y) * (ballPos.y - colision.y));
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
    std::multimap<std::pair<float, float>, Block*>* secondMap = new (std::multimap<std::pair<float, float>, Block*>);
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
        //using Map
               // colisionCheckPhase1X(ball, &rangeXball, secondMap, &secondAxis);
               // colisionCheckPhase1Y(ball, &rangeYball, secondMap, &secondAxis);
        //Using Set
        colisionCheckPhase1X(ball, &rangeXball, collisionSet);
        colisionCheckPhase1Y(ball, &rangeYball, collisionSet);
            //}
            //else {
            //    colisionCheckPhase1Y(ball, &rangeYball, secondMap, &secondAxis);
            //    colisionCheckPhase1X(ball, &rangeXball, secondMap, &secondAxis);
            //}
            //if (!secondMap->empty()) colisionCheckPhase2(ball, &rangeX, &rangeY, secondMap);
            //if (!secondMap->empty()) 
            //ball->moveBall(colisionCheckPhase2(ball, ballSecondPosition.x, ballSecondPosition.y, secondMap, &rangeXball, &rangeYball));

            //colisionCheckPhase2(ball, ballSecondPosition.x, ballSecondPosition.y, secondMap, &rangeXball, &rangeYball);
        colisionCheckPhase2(ball, ballSecondPosition.x, ballSecondPosition.y, collisionSet, &rangeXball, &rangeYball);
            //ball->ballGetStuck();
        //}
            //else ball->moveBall();
            //std::cout << "Left to move:" << ball->getDistanceLeftToMove() << std::endl;
           // ball->ballGetStuck();
        
    }
    delete secondMap;
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
