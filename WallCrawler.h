// WallCrawler.h: interface for the WallCrawler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WALLCRAWLER_H__7B6C8B08_A1FF_4672_8F63_CE76A319F141__INCLUDED_)
#define AFX_WALLCRAWLER_H__7B6C8B08_A1FF_4672_8F63_CE76A319F141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class WallCrawler  : public Moveable 
{
public:
	void move();
	void collide();
	void setCrawlDirection(behavior_t newVal);
	behavior_t getCrawlDirection();
	WallCrawler();
	WallCrawler(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain,
	behavior_t newBehavior);
	virtual ~WallCrawler();

private:
};

#endif // !defined(AFX_WALLCRAWLER_H__7B6C8B08_A1FF_4672_8F63_CE76A319F141__INCLUDED_)
