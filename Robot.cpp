// Robot.cpp: implementation of the Robot class.
//
//////////////////////////////////////////////////////////////////////

#include "Robot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Robot::Robot()
{

}

Robot::~Robot()
{

}


bool Robot::bombable()
{
	return true;
}

bool Robot::laserable()
{
	return true;
}

void Robot::setInTrain(bool newVal)
{
	inTrain = newVal;
}

void Robot::setTrainPosition(int newVal)
{
	trainPosition = newVal;
}

void Robot::setSelected(bool newVal)
{
	selected = newVal;
}

bool Robot::getSelected()
{
	return selected;
}

bool Robot::getInTrain()
{
	return inTrain;
}

int Robot::getTrainPosition()
{
	return trainPosition;
}

void Robot::collide() {

}

void Robot::move() {

}