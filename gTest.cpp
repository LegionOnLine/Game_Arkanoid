#include "gTest.h"
int mainTest(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
// *********************************
// *****    BALL TESTS SCOPE   *****
// *********************************
class BallClassTest : public ::testing::Test {
	public:
		// 22,6 angle : 5-12-13 triangle
		// 36,87 angle : 3-4-5 triangle
		float bAlfa{ 36.87 };
		float bVelocity{ 10. };
		sf::Vector2f bPossition{ 100., 100. };
		float bSize{ 10. };

		int bDirrection{ 0x10 }; //ddepend on bAlfa - manual change needed: [ 0x10 | 0x00 | 0x01 |0x11 ]
		sf::Vector2f movementVector{ 8., -6. };

		BallClassTest() {
			ball = new Ball(bAlfa, bPossition, bSize, bVelocity);
		};
		~BallClassTest() {
			delete ball;
		};
	protected:
		Ball* ball;
		virtual void setUp() {}
		virtual void TearDown() {}
};
TEST_F(BallClassTest, getBallRadius) {
	EXPECT_EQ(bSize, ball->getBallRadius()); }
TEST_F(BallClassTest, getDistanceLeftToMove) {
	EXPECT_EQ(bVelocity, ball->getDistanceLeftToMove()); }
TEST_F(BallClassTest, getBoundary) {
	EXPECT_EQ(bPossition.y - bSize, ball->getBoundary().top);
	EXPECT_EQ(bPossition.x - bSize, ball->getBoundary().left);
	EXPECT_EQ(bSize * 2, ball->getBoundary().width);
	EXPECT_EQ(bSize * 2, ball->getBoundary().height); }
TEST_F(BallClassTest, getposition) {
	EXPECT_EQ(bPossition.x, ball->getposition().x);
	EXPECT_EQ(bPossition.y, ball->getposition().y); }
TEST_F(BallClassTest, getSize) {
	EXPECT_EQ(bSize, ball->getSize());}
TEST_F(BallClassTest, getLostBall_false) {
	EXPECT_EQ(false, ball->getLostBall()); }
TEST_F(BallClassTest, getBallAlfa) {
	EXPECT_EQ(bAlfa, ball->getBallAlfa());}
TEST_F(BallClassTest, getBallDirection) {
	EXPECT_EQ(bDirrection, ball->getBallDirection()); }
TEST_F(BallClassTest, getBallVelocity) {
	EXPECT_EQ(bVelocity, ball->getBallVelocity());	}
TEST_F(BallClassTest, predictPosition) {
	EXPECT_FLOAT_EQ(bPossition.x + movementVector.x, ball->predictPosition().x);
	EXPECT_FLOAT_EQ(bPossition.y + movementVector.y, ball->predictPosition().y); }
TEST_F(BallClassTest, predictPosition_distanceToPredict) {
	float distanceToPredict{ bVelocity / 2 };
	sf::Vector2f halfPos{ bPossition.x + movementVector.x / 2, bPossition.y + movementVector.y / 2 };

	EXPECT_FLOAT_EQ(halfPos.x, ball->predictPosition(distanceToPredict).x);
	EXPECT_FLOAT_EQ(halfPos.y, ball->predictPosition(distanceToPredict).y); }
TEST_F(BallClassTest, getBallMovementVector) {
	EXPECT_NEAR(movementVector.x, ball->getBallMovementVector().x, 0.0001);
	EXPECT_NEAR(movementVector.y, ball->getBallMovementVector().y, 0.0001); }
TEST_F(BallClassTest, isBallStuck) {
	EXPECT_EQ(true, ball->isBallStuck()); }
TEST_F(BallClassTest, ballRelease) {
	EXPECT_EQ(true, ball->isBallStuck());
	ball->ballRelease();
	EXPECT_EQ(false, ball->isBallStuck()); }
TEST_F(BallClassTest, ballGetStuck) {
	ball->ballRelease();
	ball->ballGetStuck();
	EXPECT_EQ(true, ball->isBallStuck()); }
TEST_F(BallClassTest, moveBall) {
	float distanceToMove{ bVelocity / 2 };
	sf::Vector2f halfPos{ bPossition.x + movementVector.x / 2, bPossition.y + movementVector.y / 2 };
	ball->ballRelease();
	ball->moveBall(distanceToMove);
	EXPECT_NEAR(halfPos.x, ball->getposition().x, 0.0001);
	EXPECT_NEAR(halfPos.y, ball->getposition().y, 0.0001);
	EXPECT_EQ(bVelocity- distanceToMove, ball->getDistanceLeftToMove());}
TEST_F(BallClassTest, restoreMovement) {
	float distanceToMove{ bVelocity / 2 };
	sf::Vector2f halfPos{ bPossition.x + movementVector.x / 2, bPossition.y + movementVector.y / 2 };
	ball->ballRelease();
	ball->moveBall(distanceToMove);
	ball->restoreMovement();
	EXPECT_EQ(bVelocity, ball->getDistanceLeftToMove());}
TEST_F(BallClassTest, calcMovementVector) {
	ball->calcMovementVector(60.); //rotate alpha by 90 degree counterclock way
	EXPECT_NEAR(bVelocity * 0.5, ball->getBallMovementVector().x, 0.0001);
	EXPECT_NEAR(-bVelocity * std::sqrt(3)/2, ball->getBallMovementVector().y, 0.0001); }
TEST_F(BallClassTest, recalcAlpha) {
	float newAlpha{ 60. };
	ball->recalcAlpha(newAlpha);
	EXPECT_EQ(newAlpha, ball->getBallAlfa()); }
//
////collisions
//bool ballWindowCollision(sf::RenderTarget& window);
//bool ballLost(float y);
//bool ballFrameCollision(sf::Vector3f& frame);
//bool ballPaddleCollision(sf::FloatRect paddle);
//void changeDirection(float x, float y);
//void changeDirection(float beta);
//
//void ballLost();


// *********************************
// *****    BALL TESTS SCOPE   *****
// *********************************
//Block
//Game
//Paddle







