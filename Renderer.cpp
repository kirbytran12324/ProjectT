#include "Renderer.h"

using namespace std;


Renderer::Renderer(Board* pBoard, Pieces* pPieces)
{
    mBoard = pBoard;
    mPieces = pPieces;
}

void logSDLError(const std::string& msg, bool fatal)
{
    std::cout << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}


void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string& WINDOW_TITLE)

{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError("SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError("CreateWindow", true);



    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError("CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool Renderer::init(const char* WINDOW_TITLE) 
{
    initSDL(window, renderer, ScreenWidth, ScreenHeight, WINDOW_TITLE);
    return true;
}


SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void setRectPosition(SDL_Rect& rect, int x, int y, int w, int h) 
{
    rect = { x, y, w, h };
}

void moveRectPosition(SDL_Rect& rect, int x, int y) 
{
    rect.x += x;
    rect.y += y;
}


void quitSDL(SDL_Window * window, SDL_Renderer * renderer)
 {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
 }

void Renderer::updateRender() {

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (mBoard[i][j]) {
                int blockType = mBoard[i][j];

                std::string blockTexturePath = mPieces ->GetBlockTexturePath(blockType);
                SDL_Texture* blockTexture = LoadTexture(renderer,blockTexturePath);

                setRectPosition(desR, j * Board::BLOCK_SIZE, i * Board::BLOCK_SIZE);

                SDL_RenderCopy(renderer, blockTexture, nullptr, &desR);

                SDL_DestroyTexture(blockTexture);
            }
        }
    }
        for (int i = 0; i < 4; i++) {
            setRectPosition(srcR, mGame->mNextPiece * Board::BLOCK_SIZE);
            setRectPosition(desR, mGame->mNextPosX * Board::BLOCK_SIZE, mGame->mNextPosY * Board::BLOCK_SIZE);
            std::string blockTexturePath = mPieces->GetBlockTexturePath(mGame->mNextPiece);
            SDL_Texture* blockTexture = LoadTexture(renderer, blockTexturePath);
            SDL_RenderCopy(renderer, blocks_img, &srcR, &desR);
        }
        for (int i = 0; i < 4; i++) {
            setRectPosition(srcR, mGame ->mPiece * Board::BLOCK_SIZE);
            setRectPosition(desR, mGame->mPosX * Board::BLOCK_SIZE, mGame->mPosY * Board::BLOCK_SIZE);

            moveRectPosition(desR, 70, 50);
            SDL_RenderCopy(renderer, blocks_img, &srcR, &desR);
        }
    }
    
}

void Renderer::clean() {
    SDL_DestroyTexture(blocks_img);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

}



