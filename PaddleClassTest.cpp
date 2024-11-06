#include "gTest.h"

class PaddleClassTest : public ::testing::Test {
public:
	bool holdingBall{ true };
	float paddleXPosition{ 100. };
	float paddleLevel{ 500. };
	sf::Vector2f paddleSize{ 1550.f, 10.f };

	PaddleClassTest() {
		//		Paddle(float frameX, float frameY, sf::Vector2f paddleSize);
		paddle = new Paddle(paddleXPosition, paddleLevel, paddleSize);
	};
	~PaddleClassTest() {
		delete paddle;
	};
protected:
	Paddle* paddle;
	virtual void setUp() {}
	virtual void TearDown() {}
};

TEST_F(PaddleClassTest, getPosition) {
	EXPECT_FLOAT_EQ(paddleXPosition, paddle->getPosition().x);
	EXPECT_FLOAT_EQ(paddleLevel, paddle->getPosition().y);
}



// ***********************************
// *****    PADDLE TESTS SCOPE   *****
// ***********************************
// 	void draw(sf::RenderTarget& target, sf::RenderStates state) const;
//Paddle() = delete;
//Paddle(float frameX, float frameY, sf::Vector2f paddleSize);
//~Paddle() = default;
//
//void paddleWindowCollision(sf::RenderTarget& window);
//void paddleFrameCollision(sf::Vector3f frame);
//void paddleMove(int x);
//sf::FloatRect getBoundary();
//sf::Vector2f getPosition();
