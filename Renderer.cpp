#include "Renderer.h"

using namespace std;


Renderer::Renderer(Board* pBoard, Pieces* pPieces, Game* pGame)
{
    mBoard = pBoard;
    mPieces = pPieces;
    mGame = pGame;
}

void Renderer::logSDLError(const std::string& msg, bool fatal)
{
    std::cout << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath)
{
    IMG_Init(-1);
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
    {
        // Error occurred while loading the image
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr; // Return nullptr to indicate failure
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        // Error occurred while creating the texture
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        return nullptr; // Return nullptr to indicate failure
    }

    return texture;
}


void Renderer::initSDL( const std::string& WINDOW_TITLE)
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

void quitSDL(SDL_Window * window, SDL_Renderer * renderer)
 {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
 }

void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
    SDL_Rect dstRect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

int PixelcalcX(int x)
{
    return boardOffsetX + (x * Board::BLOCK_SIZE);
}

int PixelCalcY(int y)
{
    return boardOffsetY + (y * Board::BLOCK_SIZE);
}

void Renderer::updateRender()
{
    RenderBackground(renderer, background);
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (mBoard->GetBlock(i, j) != 0) {
                int blockType = mBoard->GetBlock(i, j);

                std::string blockTexturePath = mPieces->GetBlockTexturePath(blockType);
                SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
                pixelX = PixelcalcX(i);
                pixelY = PixelCalcY(j);
                RenderTexture(renderer, blockTexture, pixelX, pixelY);
            }
        }

        for (int i = 0; i < 4; i++) {
            std::string blockTexturePath = mPieces->GetBlockTexturePath(mGame->mNextPiece);
            SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
            pixelX = PixelcalcX(mGame->mNextPosX);
            pixelY = PixelCalcY(mGame->mNextPosY);
            RenderTexture(renderer, blockTexture, pixelX, pixelY);
            SDL_DestroyTexture(blockTexture);
        }

        for (int i = 0; i < 4; i++) {
            std::string blockTexturePath = mPieces->GetBlockTexturePath(mGame->mPiece);
            SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
            pixelX = PixelcalcX(mGame->mPosX);
            pixelY = PixelCalcY(mGame->mPosY);
            RenderTexture(renderer, blockTexture, pixelX, pixelY);
            SDL_DestroyTexture(blockTexture);
        }
        SDL_RenderPresent(renderer);
    }
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



