// Enemy.h: interface for the Enemy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMY_H__481A3074_A2B5_4F1E_93E5_2AAC756059D3__INCLUDED_)
#define AFX_ENEMY_H__481A3074_A2B5_4F1E_93E5_2AAC756059D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class Enemy  : public Moveable
{
public:
	bool getTurned();
	void setTurned(bool newVal);
	direction_t directionBasedOnDecoys();
	void move();
	void collide();
	Enemy(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard);
	Enemy();
	virtual ~Enemy();

private:
	bool turned;
	
};

#endif // !defined(AFX_ENEMY_H__481A3074_A2B5_4F1E_93E5_2AAC756059D3__INCLUDED_)
