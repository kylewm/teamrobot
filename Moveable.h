// Moveable.h: interface for the Moveable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEABLE_H__76F9FF7A_591A_4EFF_BC3D_CC172908DC7B__INCLUDED_)
#define AFX_MOVEABLE_H__76F9FF7A_591A_4EFF_BC3D_CC172908DC7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "team_robot.h"

class GameBoard;

class Moveable
{
public:
	void setBehavior(behavior_t newVal);
	behavior_t getBehavior();
	void setBeenLaunched(bool newVal);
	bool getBeenLaunched();
	void setHeadOn(bool newVal);
	bool getHeadOn();
	void setMoved(bool newVal);
	bool getMoved();
	bool getUTurn();
	void setUTurn(bool newVal);
	void setFinished(bool newVal);
	bool getFinished();
	void setExplodingDistance(float newVal);
	float getExplodingDistance();
	void setInTrain(bool newVal);
	bool getInTrain();
	void setJustLaunched(bool newVal);
	bool getJustLaunched();
	void setSelected(bool newVal);
	bool getSelected();
	void move(direction_t direct, int distance, int startY, int startX);
	GameBoard *getBoard();
	void setDeployedOnBoard(bool newVal);
	bool getDeployedOnBoard();
	void setExploding(bool newVal);
	bool getExploding();
	void setFalling(bool newVal);
	void setDrowning(bool newVal);
	bool getFalling();
	bool getDrowning();
	Moveable();
	Moveable(int inY, int inX, direction_t inDirection, 
		int inPrevY, int inPrevX, direction_t inPrevDirection, 
		GameBoard *inBoard, moveable_t inType, 
		bool inDeployedOnBoard);
	Moveable(int inY, int inX, direction_t inDirection, 
		int inPrevY, int inPrevX, direction_t inPrevDirection, 
		GameBoard *inBoard, moveable_t inType, 
		bool inDeployedOnBoard, bool inSelected, bool inJustLaunched,
		bool newInTrain);
	virtual ~Moveable();

	virtual void move() = 0;
	virtual void collide() = 0;

	int getY();
	int getX();
	int getPrevY();
	int getPrevX();
	direction_t getPrevDirection();
	direction_t getDirection();
	moveable_t getType();

	void setY(int newVal);
	void setX(int newVal);
	void setPrevY(int newVal);
	void setPrevX(int newVal);
	void setPrevDirection(direction_t newVal);
	void setDirection(direction_t newVal);
	void setBoard(GameBoard *newVal);
	void setType(moveable_t nt);

private:
	behavior_t behavior;
	bool beenLaunched;
	bool headOn;
	bool moved;
	bool uTurn;
	bool finished;
	float explodingDistance;
	bool inTrain;
	bool justLaunched;
	bool selected;
	bool deployedOnBoard;
	bool exploding;
	bool falling;
	bool drowning;
	GameBoard *board;
	direction_t prevDirection;
	int prevY;
	int prevX;
	int y;
	int x;
	direction_t direction;
	moveable_t type;
};

#endif // !defined(AFX_MOVEABLE_H__76F9FF7A_591A_4EFF_BC3D_CC172908DC7B__INCLUDED_)
