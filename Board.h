#ifndef _BOARD_
#define _BOARD_

// ------ Includes -----

#include "Pieces.h"
#include "Stats.h"

// ------ Defines -----

#define BOARD_WIDTH 10                
#define BOARD_HEIGHT 20               
#define PIECE_BLOCKS 5                

class Board
{
public:

	Board(Pieces* pPieces);
	static const int BLOCK_SIZE = 37;
	bool IsFreeBlock(int pX, int pY);
	bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
	void StorePiece(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines();
	bool IsGameOver();
	int GetBlock(int pX, int pY);


private:

	enum { POS_FILLED, POS_FREE };
	int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
	Pieces* mPieces;
	Stats mStats= Stats(500);
	void InitBoard();
	void DeleteLine(int pY);
};
#endif // _BOARD_
