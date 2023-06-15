#include "Renderer.h"

using namespace std;

Renderer::Renderer(Board* pBoard, Pieces* pPieces, Game* pGame,Stats* pStats)
{
	mBoard = pBoard;
	mPieces = pPieces;
	mGame = pGame;
	mStats = pStats;
}

void Renderer::logSDLError(const std::string& msg, bool fatal)
{
	std::cout << msg << " Error: " << SDL_GetError() << std::endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

#include <SDL_image.h>

// Load an image into an SDL_Texture
SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = nullptr;

	if (surface)
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

void Renderer::initSDL(const std::string& WINDOW_TITLE)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logSDLError("SDL_Init", true);

	window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (window == nullptr) logSDLError("CreateWindow", true);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) logSDLError("CreateRenderer", true);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, ScreenWidth, ScreenHeight);
	background = LoadTexture(renderer, "Data/Bg.png");
}

void RenderBackground(SDL_Renderer* renderer, SDL_Texture* background)
{
	SDL_Rect dstRect = { 0, 0, ScreenWidth, ScreenHeight };
	SDL_QueryTexture(background, NULL, NULL, &dstRect.w, &dstRect.h);
	SDL_RenderCopy(renderer, background, NULL, &dstRect);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
	int blockWidth = Board::BLOCK_SIZE, blockHeight = Board::BLOCK_SIZE;
	int textureWidth, textureHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	SDL_Rect dstRect = { x, y, blockWidth, blockHeight };
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

int PixelCalcX(int x)
{
	return boardOffsetX + (x * Board::BLOCK_SIZE);
}

int PixelCalcY(int y)
{
	return boardOffsetY + (y * Board::BLOCK_SIZE);
}

void Renderer::textRender()
{
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Data/MikadoBold.ttf", 60);
	if (font == nullptr) {
		printf("Failed to load font: %s\n", TTF_GetError());
	}
	SDL_Color textColor = { 46, 164, 72, 0 };
	std::string score = std::to_string(mStats->GetScore());
	std::string linesCleared = std::to_string(mStats->GetLinesCleared());
	std::string tetrises = std::to_string(mStats->GetTetrises());
	std::string level = std::to_string(mStats->GetLevel());

	// Create surfaces from the text using the font
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, score.c_str(), textColor);
	SDL_Surface* linesClearedSurface = TTF_RenderText_Solid(font, linesCleared.c_str(), textColor);
	SDL_Surface* tetrisesSurface = TTF_RenderText_Solid(font, tetrises.c_str(), textColor);
	SDL_Surface* levelSurface = TTF_RenderText_Solid(font, level.c_str(), textColor);

	// Convert the surfaces to textures
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_Texture* linesClearedTexture = SDL_CreateTextureFromSurface(renderer, linesClearedSurface);
	SDL_Texture* tetrisesTexture = SDL_CreateTextureFromSurface(renderer, tetrisesSurface);
	SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);

	// Set the positions for each stat
	SDL_Rect scoreRect = { 647, 438, scoreSurface->w, scoreSurface->h };
	SDL_Rect linesClearedRect = { 647, 688, linesClearedSurface->w, linesClearedSurface->h };
	SDL_Rect tetrisesRect = { 647, 810, tetrisesSurface->w, tetrisesSurface->h };
	SDL_Rect levelRect = { 647, 555 , levelSurface->w, levelSurface->h };

	// Render each stat's texture to the screen
	SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
	SDL_RenderCopy(renderer, linesClearedTexture, nullptr, &linesClearedRect);
	SDL_RenderCopy(renderer, tetrisesTexture, nullptr, &tetrisesRect);
	SDL_RenderCopy(renderer, levelTexture, nullptr, &levelRect);

	// Clean up the surfaces and textures
	SDL_FreeSurface(scoreSurface);
	SDL_FreeSurface(linesClearedSurface);
	SDL_FreeSurface(levelSurface);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(linesClearedTexture);
	SDL_DestroyTexture(levelTexture);
}


void Renderer::updateRender()
{
	RenderBackground(renderer, background);
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			int blockType = mBoard->GetBlock(j, i);
			if (blockType != 0) {
				std::string blockTexturePath = mPieces->GetBlockTexturePath(blockType);
				SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
				int pixelX = PixelCalcX(j);
				int pixelY = PixelCalcY(i);
				RenderTexture(renderer, blockTexture, pixelX, pixelY);
				SDL_DestroyTexture(blockTexture);
			}
		}
	}

	// Render current piece
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		for (int j = 0; j < PIECE_BLOCKS; j++) {
			if (mPieces->GetBlockType(mGame->mPiece, mGame->mRotation, i, j) != 0) {
				std::string blockTexturePath = mPieces->GetBlockTexturePath(mGame->mPiece);
				SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
				int pixelX = PixelCalcX(mGame->mPosX + i);
				int pixelY = PixelCalcY(mGame->mPosY + j);

				// Check if the block is within the visible area
				if (pixelX >= boardOffsetX && pixelX + Board::BLOCK_SIZE <= boardOffsetX + boardW &&
					pixelY >= boardOffsetY && pixelY + Board::BLOCK_SIZE <= boardOffsetY + boardH) {
					RenderTexture(renderer, blockTexture, pixelX, pixelY);
				}

				SDL_DestroyTexture(blockTexture); // Free the texture memory
			}
		}
	}

	// Render next piece
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		for (int j = 0; j < PIECE_BLOCKS; j++) {
			if (mPieces->GetBlockType(mGame->mNextPiece, 0, i, j) != 0) {
				std::string blockTexturePath = mPieces->GetBlockTexturePath(mGame->mNextPiece);
				SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
				int pixelX = NextX + (j * Board::BLOCK_SIZE);
				int pixelY = NextY + (i * Board::BLOCK_SIZE);
				RenderTexture(renderer, blockTexture, pixelX, pixelY);
				SDL_DestroyTexture(blockTexture); // Free the texture memory
			}
		}
	}
	Renderer::textRender();

	SDL_RenderPresent(renderer);
}

void Renderer::clean()
{
	SDL_DestroyTexture(blocks_img);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(menuTexture);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}