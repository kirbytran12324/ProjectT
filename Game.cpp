#include "Game.h"

Game::Game(Board* pBoard, Pieces* pPieces)
{
	mBoard = pBoard;
	mPieces = pPieces;
	InitGame();
}

int Game::GetRand(int pA, int pB)
{
	return rand() % (pB - pA + 1) + pA;
}

void Game::FillRandomizedBag()
{
	// Fill the bag with all pieces initially
	for (int i = 0; i < 7; i++) {
		mBag[i] = i + 1;
	}

	// Shuffle the bag using Fisher-Yates algorithm
	for (int i = 6; i >= 1; i--) {
		int randIndex = GetRand(0, i);
		int temp = mBag[i];
		mBag[i] = mBag[randIndex];
		mBag[randIndex] = temp;
	}

	mBagIndex = 0;
}

int Game::GetRandomPiece()
{
	if (mBagIndex >= 7) {
		FillRandomizedBag();
	}

	assert(mBagIndex >= 0 && mBagIndex < 7);

	int piece = mBag[mBagIndex];
	mBagIndex++;

	return piece;
}

void Game::CreateNewPiece()
{
	mPiece = mNextPiece;
	mRotation = 0;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRandomPiece();
	mNextRotation = 0;
}

void Game::InitGame()
{
	srand((unsigned int)time(NULL));
	FillRandomizedBag();

	mPiece = GetRandomPiece();
	mRotation = 0;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRandomPiece();
	mNextRotation = 0;
}