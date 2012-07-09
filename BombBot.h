// BombBot.h: interface for the BombBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOMBBOT_H__99011674_2E26_4763_BCB4_E1D562C51E74__INCLUDED_)
#define AFX_BOMBBOT_H__99011674_2E26_4763_BCB4_E1D562C51E74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class BombBot  : public Moveable
{
public:
	void collide();
	void move();
	BombBot();
	BombBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	virtual ~BombBot();

};

#endif // !defined(AFX_BOMBBOT_H__99011674_2E26_4763_BCB4_E1D562C51E74__INCLUDED_)
