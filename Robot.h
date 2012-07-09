// Robot.h: interface for the Robot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOT_H__F5779C81_736E_40BE_B28C_7ABD539C92A1__INCLUDED_)
#define AFX_ROBOT_H__F5779C81_736E_40BE_B28C_7ABD539C92A1__INCLUDED_

#include "team_robot.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Moveable.h"

class Robot : public Moveable
{
public:
	int getTrainPosition();
	bool getInTrain();
	bool getSelected();
	void setSelected(bool newVal);
	void setTrainPosition(int newVal);
	void setInTrain(bool newVal);
	virtual bool laserable();
	bool bombable();
	Robot();
	virtual ~Robot();

	virtual void move();
	virtual void collide();

private:
	bool selected;
	int trainPosition;
	bool inTrain;

};

#endif // !defined(AFX_ROBOT_H__F5779C81_736E_40BE_B28C_7ABD539C92A1__INCLUDED_)
