// PushBot.h: interface for the PushBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUSHBOT_H__DF6F7BDC_59CC_4CAF_99C2_1E6E185F6E3F__INCLUDED_)
#define AFX_PUSHBOT_H__DF6F7BDC_59CC_4CAF_99C2_1E6E185F6E3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class PushBot  : public Moveable
{
public:
	void move();
	void collide();
	PushBot();
	PushBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	virtual ~PushBot();

};

#endif // !defined(AFX_PUSHBOT_H__DF6F7BDC_59CC_4CAF_99C2_1E6E185F6E3F__INCLUDED_)
