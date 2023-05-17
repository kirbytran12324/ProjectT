#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Board.h"
#include "Pieces.h"
#include<SDL_ttf.h>

constexpr auto ScreenWidth = 820;
constexpr auto ScreenHeight = 935;

class Renderer
{
public:
    Renderer(Board* pBoard, Pieces* pPieces);
    void RenderPiece(SDL_Renderer* renderer, int pPiece, int pRotation, const SDL_Point& pPosition);
    SDL_Renderer* createWindow();
    void RenderBoard(SDL_Renderer* renderer);
private:
    Board* mBoard;
    Pieces* mPieces;
};

#endif /* WINDOW_H */
