#include "gTest.h"
int mainTest(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/* Test issues & ideas summary:
 * 
 *		->		-	need to check something
 *		***		-	idea for more complex tests
 * 
 * 
 * Ball:
 *			-> changeDirection(f,f) - change only ballMovementVector, not angle itself
 * 
 * Block:
 *			-> getBoundary() - return sf::FloatRect type, need to think if it is needed to test
 *			-> initBlock() - not all parameters can be verified
 *			-> setcolor() - need to check if it can be currently verified
 *		*** check number of hits before crushing the block /depend on hitpoints and block type
 * 
 * 
 * 
 * 
 */





// *********************************
// *****    GAME TESTS SCOPE   *****
// *********************************
//sf::CircleShape p00, p01, p10, p11;
//sf::Vertex v0, v1, v2, v3;
//float r{ 2 };
//sf::RectangleShape range;
//
//
//bool stop{ false }; //tmp
//Game();
//~Game();
//
//bool GameWorking();
//
////Basic Functionality
//void initGUI();
//void startNewGame();
//
//void initBlocks();
//void initWindow();
//void initMainFrame();
//
//void pollEvent();
//
//void colisionAlgorithm(Ball* ball);
//void colisionCheckPhase1X(Ball* ball, std::set<float>* rangeXball, std::set<Block*>* collisionSet);
//
//void colisionCheckPhase1Y(Ball* ball, std::set<float>* rangeYball, std::set<Block*>* collisionSet);
//void colisionCheckPhase1Wall(Ball* ball, std::set<float>* rangeXball, std::set<float>* rangeYball, std::set<Block*>* collisionSet);
//
//float colisionCheckPhase2(Ball* ball, sf::Vector2f ballEndPosition, std::set<Block*>* collisionSet, std::set<float>* rangeX, std::set<float>* rangeY);
//
//float collisionRespond(float alpha, char normalAxis);
//
//float calculateDistance(sf::Vector2f ballPos, sf::Vector2f colision);
//float calculateDistance(float x, float y, float a, float b);
//float calculateDistance(sf::Vector2f ball, float a, float b);
//float calculateDistanceX(float xp, float yp, float xs, float ys, float yc);
//float calculateDistanceY(float xp, float yp, float xs, float ys, float xc);
//float calculateCoords(float startPositionX, float startPositionY, float endPositionX, float endPositionY, float collisionPositionX, float collisionPositionY);
//float calculateCoords(sf::Vector2f startPosition, sf::Vector2f endPosition, float collisionPositionX, float collisionPositionY);
//
//void update();
//void updateGui();
//void updateGameText();
//
//void renderGui();
//void draw();


// **************************************
// *****    COLLISION TESTS SCOPE   *****
// **************************************
//> ball UP-RIGHT
//>>> right wall
//>>> top wall
//>>> block
//>>>>>> left wall
//>>>>>> bottom wall
//>>> paddle ?
//
//> ball UP-LEFT
//>>> top wall
//>>> left wall
//>>> block
//>>>>>> right wall
//>>>>>> bottom wall
//>>> paddle?
//
//> ball DOWN - RIGHT
//>>> right wall
//>>> block
//>>>>>> left wall
//>>>>>> top wall
//>>> paddle 
//>>>>>> top paddle
//>>>>>> left paddle 
//>>> lost ball
//
//> ball DOWN - LEFT
//>>> left wall
//>>> block
//>>>>>> right wall
//>>>>>> top wall
//>>> paddle
//>>>>>> top paddle
//>>>>>> right paddle
//>>> lost ball
//
//> hitting wall/block/paddle with different speeds 
//> check if 0, 90, 180, 270 degree is prevented to occure after bounce
//> 


// ********************************************
// *****    COLLISION CORNER-CASE SCOPE   *****
// ********************************************
// ball UP-RIGHT
// > hit at 45 degree 
// >> hitting paddle ?
// > hit top-right corrner at 45 degree
// > hit top-left corrner at near 45 degree?
// > hit at 45 degree + alfa
// > hit at 45 degree - alfa

// ball UP-LEFT
// > hit at 135 degree 
// >> hitting paddle ?
// > hit top-left corrner at 135 degree
// > hit top-left corrner at near 135 degree?
// > hit at 135 degree + alfa
// > hit at 135 degree - alfa

// ball DOWN-LEFT
// > hit at 225 degree 
// >> hitting paddle ?
// > hit at 225 degree + alfa
// > hit at 225 degree - alfa

// ball DOWN-RIGHT
// > hit at 315 degree 
// >> hitting paddle ?
// > hit at 315 degree + alfa
// > hit at 315 degree - alfa


// *************************************
// *****    GAME SCENARIOS SCOPE   *****
// *************************************

// - destroy block right before next ball would hit
// - increesing score when hitting block
// - decreesing ball number when ball lost
// - end game when all balls are lost
