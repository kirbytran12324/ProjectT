#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Board.h"
#include "Pieces.h"
#include<SDL_ttf.h>
#include "Game.h"

constexpr auto ScreenWidth = 820;
constexpr auto ScreenHeight = 935;

class Renderer
{
public:
    Renderer(Board* pBoard, Pieces* pPieces);
    void logSDLError(const std::string& msg, bool fatal);
    bool init(const char* WINDOW_TITLE);
    void clean();
    void updateRender();
    static int boardOffsetX, boardOffsetY;
private:
    Board* mBoard;
    Pieces* mPieces;
    Game* mGame;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* menuTexture = NULL;
    SDL_Texture* background = NULL;
    SDL_Texture* over = NULL;
    SDL_Texture* blocks_img = NULL;
    int pixelX = 0, pixelY = 0;

};
int Renderer::boardOffsetX = 0;
int Renderer::boardOffsetY = 0;

#endif /* WINDOW_H */
