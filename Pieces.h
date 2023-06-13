#ifndef _PIECES_
#define _PIECES_

#include <vector>
#include <string>


class Pieces
{
public:
	int GetBlockType(int pPiece, int pRotation, int pX, int pY);
	int GetXInitialPosition(int pPiece, int pRotation);
	int GetYInitialPosition(int pPiece, int pRotation);
	std::string GetBlockTexturePath(int pPiece);
	int GetBlock(int pPiece, int pRotation, int pX, int pY);
};

#endif // _PIECES_
