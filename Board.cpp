#include "Board.h"


Board::Board(Pieces* pPieces)
{

	mPieces = pPieces;


	InitBoard();
}


void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = 0;
}

// Store the blocks in the board
void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
	for (int i1 = pY, i2 = 0; i1 < pY + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pX, j2 = 0; j1 < pX + PIECE_BLOCKS; j1++, j2++)
		{
			if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
				mBoard[j1][i1] = pPiece;
		}
	}
}




bool Board::IsGameOver()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] !=0) return true;
	}
	return false;
}



void Board::DeleteLine(int pY)
{
	// Moves all the upper lines one row down
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j - 1];
		}
	}
}


//Delete all the lines that are filled

int Board::DeletePossibleLines()
{
	int ClearedLines = 0;
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] ==0) break;
			i++;
		}

		if (i == BOARD_WIDTH)
		{
			DeleteLine(j);
			ClearedLines++;
		}
	}
	return ClearedLines;
}


// Check if the block is already filled
bool Board::IsFreeBlock(int pX, int pY)
{
	if (mBoard[pX][pY] == 0) return true; else return false;
}


bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation)
{
	// Check the piece within the board
	for (int i1 = pY, i2 = 0; i1 < pY + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pX, j2 = 0; j1 < pX + PIECE_BLOCKS; j1++, j2++)
		{
			// Check if the piece is outside the limits of the board
			if (j1 < 0 ||
				j1 > BOARD_WIDTH - 1 ||
				i1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
					return false;
			}
			// Check the piece with prelaid blocks
			if (i1 >= 0)
			{
				if ((mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock(j1, i1)))
					return false;
			}
		}
	}

	return true;
}



int Board::GetBlock(int pX, int pY)
{
	return mBoard[pX][pY];
}