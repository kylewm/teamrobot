// Block.h: interface for the Block class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCK_H__5950B674_5573_43FF_9D1D_8D53B2F1DB51__INCLUDED_)
#define AFX_BLOCK_H__5950B674_5573_43FF_9D1D_8D53B2F1DB51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class Moveable;

class Block  : public Moveable
{
public:
	void move(direction_t direct, int distance, int startY, int startX);
	virtual void move();
	virtual void collide();
	Block();
	Block(int inY, int inX, direction_t inDirection, 
				   int inPrevY, int inPrevX, direction_t inPrevDirection, 
				   GameBoard *inBoard, moveable_t inType, 
				   bool inDeployedOnBoard);
	virtual ~Block();

};

#endif // !defined(AFX_BLOCK_H__5950B674_5573_43FF_9D1D_8D53B2F1DB51__INCLUDED_)
