#include "gTest.h"

class BlockClassTest : public ::testing::Test {
public:
	sf::Vector2f blockPossition{ 100., 100. };
	sf::Vector2f blockSize{ 100., 50. };
	int hp{ 1 };
	sf::Color blockColor{ sf::Color::Red };

	BlockClassTest() {
		block = new Block(blockPossition.x, blockPossition.y, blockSize.x, blockSize.y, hp, blockColor);
	};
	~BlockClassTest() {
		delete block;
	};
protected:
	Block* block;
	virtual void setUp() {}
	virtual void TearDown() {}
};

// **********************************
// *****    BLOCK TESTS SCOPE   *****
// **********************************

TEST_F(BlockClassTest, getId) {
	EXPECT_EQ(0, block->getId());
	Block* block2 = new Block(blockPossition.x, blockPossition.y, blockSize.x, blockSize.y, hp, sf::Color::Red);
	EXPECT_EQ(1, block2->getId());
	delete block2;
}
TEST_F(BlockClassTest, getBlockSize) {
	EXPECT_EQ(blockSize, block->getBlockSize());
}
TEST_F(BlockClassTest, printableObj) {
	EXPECT_EQ(true, block->printableObj());
}
TEST_F(BlockClassTest, changeState) {
	block->changeState();
	EXPECT_EQ(false, block->printableObj());
}
TEST_F(BlockClassTest, getPoints) {
	EXPECT_EQ(hp, block->getPoints());
}
//TEST_F(BlockClassTest, getBoundary) {
//	//this will return sf::FloatRect type
//	EXPECT_EQ(blockPossition, block->getBoundary());}
//	Block(); - only used for Paddle class and Walls ?
TEST_F(BlockClassTest, initBlock) {
	Block* emptyBlock = new Block();
	sf::Vector2f emptyBlockPossition{ 10., 10. };
	sf::Vector2f emptyBlockSize{ 10., 5. };
	int emptyBlockHp{ -1 };
	sf::Color emptyBlockColor{ sf::Color::White };

	emptyBlock->initBlock(emptyBlockPossition.x,
		emptyBlockPossition.y,
		emptyBlockSize.x,
		emptyBlockSize.y,
		emptyBlockHp,
		emptyBlockColor);
	//EXPECT_EQ(, emptyBlock->getBoundary());
	EXPECT_EQ(emptyBlockSize, emptyBlock->getBlockSize());
	EXPECT_EQ(true, emptyBlock->printableObj());
	EXPECT_EQ(emptyBlockHp, emptyBlock->getPoints());
}
