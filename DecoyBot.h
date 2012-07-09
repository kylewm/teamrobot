// DecoyBot.h: interface for the DecoyBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECOYBOT_H__4ADD635F_F6DB_4DBB_A93A_533DC6A9CD02__INCLUDED_)
#define AFX_DECOYBOT_H__4ADD635F_F6DB_4DBB_A93A_533DC6A9CD02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class DecoyBot  : public Moveable
{

public:
	void collide();
	void move();
	DecoyBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	DecoyBot();
	virtual ~DecoyBot();

private:
	bool active;
};

#endif // !defined(AFX_DECOYBOT_H__4ADD635F_F6DB_4DBB_A93A_533DC6A9CD02__INCLUDED_)
