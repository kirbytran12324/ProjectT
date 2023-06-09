#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>
#include <cstdlib>
#include <cassert>

class Game
{
public:
	Game(Board* pBoard, Pieces* pPieces);

	void CreateNewPiece();
	int mPosX, mPosY;				// Position of the piece that is falling down
	int mPiece, mRotation;			// Kind and rotation the piece that is falling down
	int mBag[7];                        // Array to store the pieces in the bag
	int mBagIndex;                      // Index to keep track of the current position in the bag
	int mNextPiece, mNextRotation;	// Kind and rotation of the next piece

private:
	int mScreenHeight;				// Screen height in pixels
	Board* mBoard;
	Pieces* mPieces;
	void FillRandomizedBag();           // Function to fill the bag with random pieces
	int GetRandomPiece();               // Function to get the next piece from the bag
	void InitGame();
	int GetRand(int a, int b);
};

#endif //_GAME_
