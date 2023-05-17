#include "Renderer.h"




Renderer::Renderer(Board* pBoard, Pieces* pPieces)
{
    mBoard = pBoard;
    mPieces = pPieces;
    SDL_Renderer * mRenderer = createWindow();
}

SDL_Renderer* Renderer::createWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Unable to initialize SDL %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 820, 935, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Could not create window %s", SDL_GetError());
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Could not create renderer %s", SDL_GetError());
    }

    SDL_Surface* surface = IMG_Load("Data/Bg.png");
    if (surface == NULL)
    {
        printf("Could not load image %s", IMG_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Could not create texture %s", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    return renderer;
}


SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


void Renderer::RenderPiece(SDL_Renderer* renderer, int pPiece, int pRotation, const SDL_Point& pPosition)
{

    // Calculate the screen position of the piece based on its grid position
    const int blockWidth = 70;
    const int blockHeight = 70;
    const int xOffset = (ScreenWidth - blockWidth * BOARD_WIDTH) / 2;
    const int yOffset = (ScreenHeight - blockHeight * BOARD_HEIGHT) / 2;

    std::string texturePath = mPieces->GetBlockTexturePath(pPiece);
    for (int i = 0; i < PIECE_BLOCKS; ++i)
    {
        for (int j = 0; j < PIECE_BLOCKS; j++)
        {
            int blockIndex = mPieces->GetBlock(pPiece, pRotation, j, i);
            if (blockIndex == 0)
            {
                continue;
            }
            // Load the texture and render it at the correct position
            SDL_Texture* texture = LoadTexture(renderer, texturePath);

            const int x = (j * blockWidth) + xOffset + (pPosition.x * blockWidth);
            const int y = (i * blockHeight) + yOffset + (pPosition.y * blockHeight);


            SDL_Rect destRect = { x, y, blockWidth, blockHeight };
            SDL_RenderCopy(renderer, texture, NULL, &destRect);
            SDL_DestroyTexture(texture);
        }
        }
        
}

void Renderer::RenderBoard(SDL_Renderer* renderer)
{
    // Calculate the screen position of the board based on its dimensions
    const int blockWidth = 70;
    const int blockHeight = 70;
    const int xOffset = (ScreenWidth - blockWidth * BOARD_WIDTH) / 2;
    const int yOffset = (ScreenHeight - blockHeight * BOARD_HEIGHT) / 2;

    // Render each block in the board
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            // Get the block index and texture path for the current block in the board
            int blockIndex = mBoard->GetBlock(j, i);
            std::string texturePath = mPieces->GetBlockTexturePath(blockIndex);

            // Load the texture and render it at the correct position
            SDL_Texture* texture = LoadTexture(renderer, texturePath);

            const int x = j * blockWidth + xOffset;
            const int y = i * blockHeight + yOffset;

            SDL_Rect destRect = { x, y, blockWidth, blockHeight };
            SDL_RenderCopy(renderer, texture, NULL, &destRect);

            SDL_DestroyTexture(texture);
        }
    }
}



