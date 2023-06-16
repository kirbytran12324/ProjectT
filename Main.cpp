#include "Pieces.h"
#include "Board.h"
#include "Game.h"
#include "Stats.h"
#include "Renderer.h"
#include "IO.h"
#undef main

int main()
{
	int WAIT_TIME = 500;
	bool quit = false;
	unsigned long lastDropTime = SDL_GetTicks();
	unsigned long lastHeld = 0;
	int HoldCooldown = 80;
	IO mIO;

	Pieces mPieces;

	Stats mStats(WAIT_TIME);

	Board mBoard(&mPieces, &mStats);

	Game mGame(&mBoard, &mPieces);



	Renderer renderer(&mBoard, &mPieces, &mGame, &mStats);

	renderer.initSDL("Tetris");

	while (!quit)
	{
		while (mIO.PollEvent())
		{
			if (mIO.WasKeyDown(SDL_SCANCODE_Z))
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation - 1) % 4))
					if ((mGame.mRotation - 1) < 0)
					{
						mGame.mRotation = 3;
					}
					else mGame.mRotation = (mGame.mRotation - 1) % 4;
			}
			else if (mIO.WasKeyDown(SDL_SCANCODE_X))
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					mGame.mRotation = (mGame.mRotation + 1) % 4;
			}
			else if (mIO.WasKeyDown(SDL_SCANCODE_SPACE))
			{
				while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

				mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					quit = true;
				}

				mGame.CreateNewPiece();
			}
		}
		if (mIO.IsKeyDown(SDL_SCANCODE_ESCAPE) && SDL_GetTicks() - lastHeld >= HoldCooldown)
		{
			quit = true;
		}
		else if (mIO.IsKeyDown(SDL_SCANCODE_LEFT) && SDL_GetTicks() - lastHeld >= HoldCooldown)
		{
			lastHeld = SDL_GetTicks();
			if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX--;
		}
		else if (mIO.IsKeyDown(SDL_SCANCODE_RIGHT) && SDL_GetTicks() - lastHeld >= HoldCooldown)
		{
			lastHeld = SDL_GetTicks();
			if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX++;
		}
		else if (mIO.IsKeyDown(SDL_SCANCODE_DOWN) && SDL_GetTicks() - lastHeld >= HoldCooldown)
		{
			lastHeld = SDL_GetTicks();
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
				mGame.mPosY++;
		}

		unsigned long currentTime = SDL_GetTicks();

		if ((currentTime - lastDropTime) >= WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
				mBoard.DeletePossibleLines();
				if (mBoard.IsGameOver())
				{
					quit = true;
				}
				mGame.CreateNewPiece();
			}
			lastDropTime = currentTime;
		}
		renderer.updateRender();
	}
	renderer.clean();
	return 0;
}