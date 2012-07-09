// DrillBot.h: interface for the DrillBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRILLBOT_H__2DFC3676_79B7_4BA4_8B69_C9FFBB0DEA86__INCLUDED_)
#define AFX_DRILLBOT_H__2DFC3676_79B7_4BA4_8B69_C9FFBB0DEA86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class DrillBot  :public Moveable
{
public:
	void collide();
	void move();
	DrillBot();
	DrillBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	virtual ~DrillBot();

};

#endif // !defined(AFX_DRILLBOT_H__2DFC3676_79B7_4BA4_8B69_C9FFBB0DEA86__INCLUDED_)
