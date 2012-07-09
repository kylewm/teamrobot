// SwimBot.h: interface for the SwimBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWIMBOT_H__C74D06E9_27A8_42CA_8CAA_326B5B2F79C1__INCLUDED_)
#define AFX_SWIMBOT_H__C74D06E9_27A8_42CA_8CAA_326B5B2F79C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class SwimBot  : public Moveable
{
public:
	void move();
	void collide();
	SwimBot();
	virtual ~SwimBot();
	SwimBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
};

#endif // !defined(AFX_SWIMBOT_H__C74D06E9_27A8_42CA_8CAA_326B5B2F79C1__INCLUDED_)
