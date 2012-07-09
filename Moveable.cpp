// Moveable.cpp: implementation of the Moveable class.
//
//////////////////////////////////////////////////////////////////////

#include "Moveable.h"
#include "GameBoard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Moveable::Moveable()
{

}

Moveable::Moveable(int inY, int inX, direction_t inDirection, 
				   int inPrevY, int inPrevX, direction_t inPrevDirection, 
				   GameBoard *inBoard, moveable_t inType, 
				   bool inDeployedOnBoard) {
	setX(inX);
	setY(inY);
	setDirection(inDirection);
	setPrevX(inPrevX);
	setPrevY(inPrevY);
	setPrevDirection(inPrevDirection);
	setBoard(inBoard);
	type = inType;
	setDeployedOnBoard(inDeployedOnBoard);
	setSelected(false);
	setJustLaunched(false);
	setInTrain(false);
	setExploding(false);
	setDrowning(false);
	setFalling(false);
	setExplodingDistance(1.0f);
	finished = false;
	uTurn = false;
	headOn = false;
	beenLaunched = false;
	behavior = NOBEHAVIOR;
}

Moveable::Moveable(int inY, int inX, direction_t inDirection, 
				   int inPrevY, int inPrevX, direction_t inPrevDirection, 
				   GameBoard *inBoard, moveable_t inType, 
				   bool inDeployedOnBoard, bool inSelected, bool inJustLaunched,
				   bool newInTrain)
{
	setX(inX);
	setY(inY);
	setDirection(inDirection);
	setPrevX(inPrevX);
	setPrevY(inPrevY);
	setPrevDirection(inPrevDirection);
	setBoard(inBoard);
	type = inType;
	setDeployedOnBoard(inDeployedOnBoard);
	setSelected(inSelected);
	setJustLaunched(inJustLaunched);
	setExploding(false);
	setDrowning(false);
	setFalling(false);
	setInTrain(newInTrain);
	setExplodingDistance(1.0f);
	finished = false;
	uTurn = false;
	headOn = false;
	beenLaunched = false;
	behavior = NOBEHAVIOR;
}

Moveable::~Moveable()
{

}

void Moveable::setBoard(GameBoard *newVal)
{
	board = newVal;
}

direction_t Moveable::getDirection()
{
	return direction;
}

direction_t Moveable::getPrevDirection()
{
	return prevDirection;
}

int Moveable::getPrevX()
{
	return prevX;
}

int Moveable::getPrevY()
{
	return prevY;
}

int Moveable::getX()
{
	return x;
}

int Moveable::getY()
{
	return y;
}

moveable_t Moveable::getType() 
{
	return type;
}

void Moveable::setDirection(direction_t newVal)
{
	direction = newVal;
}

void Moveable::setPrevDirection(direction_t newVal)
{
	prevDirection = newVal;
}

void Moveable::setPrevX(int newVal)
{
	prevX = newVal;
}

void Moveable::setPrevY(int newVal)
{
	prevY = newVal;
}

void Moveable::setX(int newVal)
{
	x = newVal;
}

void Moveable::setY(int newVal)
{
	y = newVal;
}

void Moveable::setType(moveable_t nt) {
	if(type != CABOOSEBOT) {
		type = nt;
	}
}

bool Moveable::getDrowning()
{
	return drowning;
}

bool Moveable::getFalling()
{
	return falling;
}

void Moveable::setDrowning(bool newVal)
{
	drowning = newVal;
}

void Moveable::setFalling(bool newVal)
{
	falling = newVal;
}

bool Moveable::getExploding()
{
	return exploding;
}

void Moveable::setExploding(bool newVal)
{
	exploding = newVal;
}

bool Moveable::getDeployedOnBoard()
{
	return deployedOnBoard;
}

void Moveable::setDeployedOnBoard(bool newVal)
{
	deployedOnBoard = newVal;
}

GameBoard *Moveable::getBoard()
{
	return board;
}

void Moveable::move(direction_t direct, int distance, int startY, int startX)
{
	switch (direct) {
	case UP:
		setY(getY() - distance);
		break;
	case DOWN:
		setY(getY() + distance);
		break;
	case LEFT:
		setX(getX() - distance);
		break;
	case RIGHT:
		setX(getX() + distance);
		break;
	}
	getBoard()->addMoveableAt(getY(), getX(), this);
	getBoard()->removeMoveableAt(startY, startX, this);
	getBoard()->addToChangeList(getY(), getX());
	getBoard()->addToChangeList(startY, startX);
}

bool Moveable::getSelected()
{
	return selected;
}

void Moveable::setSelected(bool newVal)
{
	selected = newVal;
}

bool Moveable::getJustLaunched()
{
	return justLaunched;
}

void Moveable::setJustLaunched(bool newVal)
{
	justLaunched = newVal;
}	

bool Moveable::getInTrain()
{
	return inTrain;
}

void Moveable::setInTrain(bool newVal)
{
	inTrain = newVal;
}

float Moveable::getExplodingDistance()
{
	return explodingDistance;
}

void Moveable::setExplodingDistance(float newVal)
{
	explodingDistance = newVal;
}

bool Moveable::getFinished()
{
	return finished;
}

void Moveable::setFinished(bool newVal)
{
	finished = newVal;
}

void Moveable::setUTurn(bool newVal)
{
	uTurn = newVal;
}

bool Moveable::getUTurn()
{
	return uTurn;
}

bool Moveable::getMoved()
{
	return moved;
}

void Moveable::setMoved(bool newVal)
{
	moved = newVal;
}


bool Moveable::getHeadOn()
{
	return headOn;
}

void Moveable::setHeadOn(bool newVal)
{
	headOn = newVal;
}

bool Moveable::getBeenLaunched()
{
	return beenLaunched;
}

void Moveable::setBeenLaunched(bool newVal)
{
	beenLaunched = newVal;
}

behavior_t Moveable::getBehavior()
{
	return behavior;
}

void Moveable::setBehavior(behavior_t newVal)
{
	behavior = newVal;
}
