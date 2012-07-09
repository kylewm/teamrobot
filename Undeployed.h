// Undeployed.h: interface for the Undeployed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDEPLOYED_H__FC0DA2F6_EC91_4BCC_89AF_34B25C9B770A__INCLUDED_)
#define AFX_UNDEPLOYED_H__FC0DA2F6_EC91_4BCC_89AF_34B25C9B770A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class Undeployed  : public Moveable
{
public:
	void collide();
	void move();
	Undeployed();
	Undeployed(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	virtual ~Undeployed();

};

#endif // !defined(AFX_UNDEPLOYED_H__FC0DA2F6_EC91_4BCC_89AF_34B25C9B770A__INCLUDED_)
