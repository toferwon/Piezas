/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	Piezas testBoard;
	ASSERT_TRUE(true);
}

TEST(PiezasTest, checkBoardInit)
{
  Piezas testBoard;
	for(int i=0;i<BOARD_ROWS;i++) {
		for(int j=0;j<BOARD_COLS;j++) {
  		ASSERT_EQ(testBoard.pieceAt(i,j), Blank);
		}
	}
}

TEST(PiezasTest, checkReset)
{
  Piezas testBoard;
	for(int i=0;i<BOARD_ROWS;i++) {
		for(int j=0;j<BOARD_COLS;j++) {
			testBoard.dropPiece(j);
		}
	}
	testBoard.reset();
	for(int i=0;i<BOARD_ROWS;i++) {
		for(int j=0;j<BOARD_COLS;j++) {
  		ASSERT_EQ(testBoard.pieceAt(i,j), Blank);
		}
	}
}


TEST(PiezasTest, invalidPieceLookups)
{
  Piezas testBoard;
	ASSERT_EQ(testBoard.pieceAt(BOARD_ROWS,BOARD_COLS),Invalid);
	ASSERT_EQ(testBoard.pieceAt(BOARD_ROWS,0),Invalid);
  ASSERT_EQ(testBoard.pieceAt(0,BOARD_COLS),Invalid);
	ASSERT_EQ(testBoard.pieceAt(-1,-1),Invalid);
	ASSERT_EQ(testBoard.pieceAt(-1,0),Invalid);
	ASSERT_EQ(testBoard.pieceAt(0,-1),Invalid);
}

TEST(PiezasTest, invalidPlacements)
{
  Piezas testBoard;
  ASSERT_EQ(testBoard.dropPiece(BOARD_COLS),Invalid);
	ASSERT_EQ(testBoard.dropPiece(-1),Invalid);
}

TEST(PiezasTest, checkStartingWinner)
{
  Piezas testBoard;
  ASSERT_EQ(testBoard.gameState(), Invalid);
}

TEST(PiezasTest, checkDropChangesTurn)
{
  Piezas testBoard;
	int eCnt=0;
	for(int i=0;i<BOARD_ROWS;i++) {
		for(int j=0;j<BOARD_COLS;j++) {
			if( ( eCnt ) % 2) {
  			ASSERT_EQ(testBoard.dropPiece(j), O);
			} else {
				ASSERT_EQ(testBoard.dropPiece(j), X);
			}
			eCnt++;
		}
	}
}

TEST(PiezasTest, checkDropChangesTurnonInvalid)
{
  Piezas testBoard;
	ASSERT_EQ(testBoard.dropPiece(BOARD_COLS), Invalid);
	ASSERT_EQ(testBoard.dropPiece(0), O);
	ASSERT_EQ(testBoard.dropPiece(0), X);
}

TEST(PiezasTest, checkDropChangesTurnonBlank)
{
  Piezas testBoard;
	if(BOARD_COLS==1) {
		ASSERT_TRUE(true);
	}
	for(int i=0;i<BOARD_ROWS;i++) {
		testBoard.dropPiece(0);
	}
	ASSERT_EQ(testBoard.dropPiece(0), Blank);
	if(BOARD_ROWS % 2) {
		ASSERT_NE(testBoard.dropPiece(1), O);
	} else {
		ASSERT_NE(testBoard.dropPiece(1), X);
	}
}


 TEST(PiezasTest, checkDropFull)
 {
   Piezas testBoard;
	 for(int i=0;i<BOARD_ROWS;i++) {
		 for(int j=0;j<BOARD_COLS;j++) {
			 testBoard.dropPiece(j);
		 }
	 }
	 for(int j=0;j<BOARD_COLS;j++) {
   	 ASSERT_EQ(testBoard.dropPiece(j), Blank);
	 }
 }

 TEST(PiezasTest, checkTie)
 {
	 Piezas testBoard;
	for(int i=0;i<BOARD_ROWS;i++) {
		for(int j=0;j<BOARD_COLS;j++) {
			testBoard.dropPiece(j);
		}
	}
	ASSERT_EQ(testBoard.gameState(), Blank);
 }

 TEST(PiezasTest, checkPartialInvalidWinner)
 {
	 Piezas testBoard;
	 int trackers[2][2] {{0,0},{0,BOARD_COLS-1}};
	 while(trackers[1][0] <= BOARD_ROWS){
		 while(trackers[0][1] <= trackers[1][1]){
				testBoard.dropPiece(trackers[1][1]);
				testBoard.dropPiece(trackers[0][1]);
				trackers[1][1]--;
					if(trackers[0][0] == BOARD_ROWS) {
						trackers[0][0] = 0;
						trackers[0][1]++;
					} else {
						trackers[0][0]++;
					}
				}
				trackers[1][0]++;
			}
			ASSERT_EQ(testBoard.gameState(), Invalid);
		}


		 TEST(PiezasTest, checkWinnerAllX)
		 {
			 //Piezas testBoard;
			 // int trackers[2][2] {{0,0},{0,BOARD_COLS-1}};
			 // while(trackers[1][0] <= BOARD_ROWS){
				//  while(trackers[0][1] <= trackers[1][1]){
				// 		testBoard.dropPiece(trackers[1][1]);
				// 		testBoard.dropPiece(trackers[0][1]);
				// 		trackers[1][1]--;
				// 			if(trackers[0][0] == BOARD_ROWS) {
				// 				trackers[0][0] = 0;
				// 				trackers[0][1]++;
				// 			} else {
				// 				trackers[0][0]++;
				// 			}
				// 		}
				// 		trackers[1][0]++;
				// 		trackers[1][1] = BOARD_COLS-1;
				// 	}
				// 	ASSERT_EQ(testBoard.pieceAt(1,BOARD_COLS-1),X);
				Piezas testBoard;
				int eCnt=0;
				for(int i=0;i<BOARD_ROWS;i++) {
					for(int j=0;j<BOARD_COLS;j++) {
						if( ( eCnt ) % 2) {
			  			testBoard.dropPiece(-1);
							j--;
						} else {
							testBoard.dropPiece(j);
						}
						eCnt++;
					}
				}
					ASSERT_EQ(testBoard.gameState(), X);
				}

				TEST(PiezasTest, checkWinnerHorizontal)
		 	 {
		 			Piezas testBoard;
		 			int eCnt=0;
		 			for(int i=0;i<BOARD_ROWS;i++) {
		 				for(int j=0;j<BOARD_COLS;j++) {
		 					if( ( eCnt ) % 2) {
								testBoard.dropPiece(j);
		 					} else {
		 						testBoard.dropPiece(j);
								if(i!=0) {
									testBoard.dropPiece(-1);
			 						j--;
								} else {
									testBoard.dropPiece(j);
								}
		 					}
		 					eCnt++;
		 				}
		 			}
		 				ASSERT_EQ(testBoard.gameState(), O);
		 			}

					TEST(PiezasTest, checkWinnerVertical)
			 	 {
			 			Piezas testBoard;
			 			int eCnt=0;
			 			for(int i=0;i<BOARD_ROWS;i++) {
			 				for(int j=0;j<BOARD_COLS;j++) {
			 					if( ( eCnt ) % 2) {
									testBoard.dropPiece(j);
			 					} else {
			 						testBoard.dropPiece(j);
									if(j!=0) {
										testBoard.dropPiece(-1);
				 						j--;
									} else {
										testBoard.dropPiece(j);
									}
			 					}
			 					eCnt++;
			 				}
			 			}
			 				ASSERT_EQ(testBoard.gameState(), O);
			 			}
