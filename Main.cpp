#include "Pieces.h"
#include "Board.h"
#include "Game.h"
#include "Stats.h"
#include "Renderer.h"
#include "IO.h"
#undef main

int main()
{
    
    int mScreenWidth = 820;
    int mScreenHeight = 935;

    IO mIO;

    Pieces mPieces;

    Board mBoard(&mPieces, mScreenHeight);

    Game mGame(&mBoard, &mPieces, mScreenHeight);


    Renderer mRenderer(&mBoard, &mPieces);


    long WAIT_TIME = 500;


    unsigned long mTime1 = SDL_GetTicks();

    SDL_Renderer* renderer = mRenderer.createWindow();

    bool quit = false;

    unsigned long lastDropTime = SDL_GetTicks();


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
            else if (mIO.IsKeyDown(SDL_SCANCODE_SPACE))
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
        if (mIO.IsKeyDown(SDL_SCANCODE_ESCAPE))
        {
            quit = true;
        }
        else if (mIO.IsKeyDown(SDL_SCANCODE_LEFT))
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX--;
        }
        else if (mIO.IsKeyDown(SDL_SCANCODE_RIGHT))
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX++;
        }
        else if (mIO.IsKeyDown(SDL_SCANCODE_DOWN))
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
                mGame.mPosY++;
        }

        unsigned long currentTime = SDL_GetTicks();

        if (currentTime - lastDropTime >= WAIT_TIME) 
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) 
            {
                mGame.mPosY++;
            }
            else 
            {
                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                mBoard.DeletePossibleLines();
                if (mBoard.IsGameOver()) {
                    quit = true;
                }
                mGame.CreateNewPiece();
            }
            lastDropTime = currentTime;
        }

        SDL_Point CurrentPos = { mGame.mPosX, mGame.mPosY };
        mRenderer.RenderPiece(renderer, mGame.mPiece, mGame.mRotation, CurrentPos);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}