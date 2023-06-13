#include "Pieces.h"

using namespace std;

char mPieces[8 /*kind -1 */][4 /* rotation */][5 /* horizontal blocks */][5 /* vertical blocks */] =
{
    {},
    // O
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0}
        }
       },

    // I
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 2, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {2, 2, 2, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 2, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0}
        }
       }
      ,
    // L
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 3, 3, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 3, 3, 3, 0},
        {0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 3, 3, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0},
        {0, 3, 3, 3, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        }
       },
    // J
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 4, 0, 0},
        {0, 0, 4, 0, 0},
        {0, 4, 4, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 4, 0, 0, 0},
        {0, 4, 4, 4, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 4, 4, 0},
        {0, 0, 4, 0, 0},
        {0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 4, 4, 4, 0},
        {0, 0, 0, 4, 0},
        {0, 0, 0, 0, 0}
        }
       },
    // Z
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 5, 0},
        {0, 0, 5, 5, 0},
        {0, 0, 5, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 5, 5, 0, 0},
        {0, 0, 5, 5, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 5, 0, 0},
        {0, 5, 5, 0, 0},
        {0, 5, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 5, 5, 0, 0},
        {0, 0, 5, 5, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        }
       },
    // S
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 6, 0, 0},
        {0, 0, 6, 6, 0},
        {0, 0, 0, 6, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 6, 6, 0},
        {0, 6, 6, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 6, 0, 0, 0},
        {0, 6, 6, 0, 0},
        {0, 0, 6, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 6, 6, 0},
        {0, 6, 6, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        }
       },
    // T
      {
       {
        {0, 0, 0, 0, 0},
        {0, 0, 7, 0, 0},
        {0, 0, 7, 7, 0},
        {0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 7, 7, 7, 0},
        {0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 7, 0, 0},
        {0, 7, 7, 0, 0},
        {0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0}
        },
       {
        {0, 0, 0, 0, 0},
        {0, 0, 7, 0, 0},
        {0, 7, 7, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        }
       }
};


// Displacement of the piece to the position where it is first drawn in the board when it is created
int mPiecesInitialPosition[7 /*kind */][4 /* rotation */][2 /* position */] =
{
    /* O */
      {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -3}
       },
    /* I */
      {
        {-2, -2},
        {-2, -3},
        {-2, -2},
        {-2, -3}
       },
    /* L */
      {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -2}
       },
    /* J */
      {
        {-2, -3},
        {-2, -2},
        {-2, -3},
        {-2, -3}
       },
    /* Z */
      {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -2}
       },
    /* S */
      {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -2}
       },
    /* T */
      {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -2}
       },
};



int Pieces::GetBlockType(int pPiece, int pRotation, int pX, int pY)
{
    return mPieces[pPiece][pRotation][pX][pY];
}

int Pieces::GetXInitialPosition(int pPiece, int pRotation)
{
    return mPiecesInitialPosition[pPiece][pRotation][0];
}

int Pieces::GetYInitialPosition(int pPiece, int pRotation)
{
    return mPiecesInitialPosition[pPiece][pRotation][1];
}

string Pieces::GetBlockTexturePath(int pPiece)
{
    switch (pPiece)
    {
    case 1:
        return "Data/Pieces/O.png";
    case 2:
        return "Data/Pieces/I.png";
    case 3:
        return "Data/Pieces/L.png";
    case 4:
        return "Data/Pieces/J.png";
    case 5:
        return "Data/Pieces/Z.png";
    case 6:
        return "Data/Pieces/S.png";
    case 7:
        return "Data/Pieces/T.png";
    default:
        return ""; // Add a default case to handle unknown piece values
    }
}


int Pieces::GetBlock(int pPiece, int pRotation, int pX, int pY)
{
    int index = mPieces[pPiece][pRotation][pX][pY];
    return index;
}

