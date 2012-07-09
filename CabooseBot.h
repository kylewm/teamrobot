// CabooseBot.h: interface for the CabooseBot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CABOOSEBOT_H__F84303AD_BB8D_42DC_AE3B_246D0546339C__INCLUDED_)
#define AFX_CABOOSEBOT_H__F84303AD_BB8D_42DC_AE3B_246D0546339C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class CabooseBot  : public Moveable
{
public:
	void collide();
	void move();
	CabooseBot();
	CabooseBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain);
	virtual ~CabooseBot();

};

#endif // !defined(AFX_CABOOSEBOT_H__F84303AD_BB8D_42DC_AE3B_246D0546339C__INCLUDED_)
