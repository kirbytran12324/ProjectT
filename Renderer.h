#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Board.h"
#include "Pieces.h"
#include <SDL_ttf.h>
#include "Game.h"
#include "Stats.h"

constexpr auto ScreenWidth = 820;
constexpr auto ScreenHeight = 935;
constexpr auto boardOffsetX = 130;
constexpr auto boardOffsetY = 116;
constexpr auto boardW = 374;
constexpr auto boardH = 740;

class Renderer
{
public:
	Renderer(Board* pBoard, Pieces* pPieces, Game* pGame, Stats* mStats);
	void logSDLError(const std::string& msg, bool fatal);
	void initSDL(const std::string& WINDOW_TITLE);
	void clean();
	void updateRender();
	void textRender();

private:
	Board* mBoard;
	Pieces* mPieces;
	Game* mGame;
	Stats* mStats;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* menuTexture = NULL;
	SDL_Texture* background = NULL;
	SDL_Texture* over = NULL;
	SDL_Texture* blocks_img = NULL;
	SDL_Surface* surface = NULL;
	int pixelX = NULL, pixelY = NULL;
	int NextX = 585, NextY = 110;
};

#endif /* WINDOW_H */
