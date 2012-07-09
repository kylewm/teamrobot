// BridgeBot.h: interface for the BridgeBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRIDGEBOT_H__CC6A7B56_117A_4B9A_A4EC_1BE3BE7C283F__INCLUDED_)
#define AFX_BRIDGEBOT_H__CC6A7B56_117A_4B9A_A4EC_1BE3BE7C283F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class BridgeBot  : public Moveable
{
public:
	void collide();
	void move();
	BridgeBot();
	BridgeBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	virtual ~BridgeBot();

};

#endif // !defined(AFX_BRIDGEBOT_H__CC6A7B56_117A_4B9A_A4EC_1BE3BE7C283F__INCLUDED_)
