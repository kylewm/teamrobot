// TurnBot.h: interface for the TurnBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TURNBOT_H__7173EA7A_150C_41E5_990B_052AF7EC1D9D__INCLUDED_)
#define AFX_TURNBOT_H__7173EA7A_150C_41E5_990B_052AF7EC1D9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class TurnBot  : public Moveable
{
public:
	void collide();
	void setTurnDirection(behavior_t newVal);
	behavior_t getTurnDirection();
	void move();
	TurnBot();
	TurnBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain, behavior_t newBehavior);
	virtual ~TurnBot();

private:
};

#endif // !defined(AFX_TURNBOT_H__7173EA7A_150C_41E5_990B_052AF7EC1D9D__INCLUDED_)
