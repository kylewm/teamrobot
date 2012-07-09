// Block.cpp: implementation of the Block class.
//
//////////////////////////////////////////////////////////////////////

#include "Block.h"
#include "GameTile.h"
#include "GameBoard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Block::Block()
{

}

Block::Block(int inY, int inX, direction_t inDirection, 
				   int inPrevY, int inPrevX, direction_t inPrevDirection, 
				   GameBoard *inBoard, moveable_t inType, 
				   bool inDeployedOnBoard)
				   : Moveable(inY, inX, inDirection, 
				   inPrevY, inPrevX, inPrevDirection, 
				   inBoard, inType, 
				   inDeployedOnBoard)

{
}

Block::~Block()
{

}

void Block::move() {
	setPrevY(getY());
	setPrevX(getX());
	setPrevDirection(getDirection());	
}


void Block::collide() {
	GameTile *curTile = getBoard()->getTileAt(getY(), getX());

	switch(curTile->getPrimaryTerrain()) {
	case NS_REDGATE:
	case NS_BLUEGATE:
	case NS_GREENGATE:
	case NS_ORANGEGATE:
	case EW_REDGATE:
	case EW_BLUEGATE:
	case EW_GREENGATE:
	case EW_ORANGEGATE:
		setExploding(true);
		setExplodingDistance(0.5);
		break;
	case WATER:
		setDrowning(true);
		break;
	case PIT:
		setFalling(true);
		break;
	case REDSWITCH_UP:
		getBoard()->updateGateList(NS_REDGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), REDSWITCH_DOWN);
		break;
	case HEAVYREDSWITCH_UP:
		getBoard()->updateGateList(NS_REDGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), HEAVYREDSWITCH_DOWN);
		break;
	case BLUESWITCH_UP:
		getBoard()->updateGateList(NS_BLUEGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), BLUESWITCH_DOWN);
		break;
	case HEAVYBLUESWITCH_UP:
		getBoard()->updateGateList(NS_BLUEGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), HEAVYBLUESWITCH_DOWN);
		break;
	case GREENSWITCH_UP:
		getBoard()->updateGateList(NS_GREENGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), GREENSWITCH_DOWN);
		break;
	case HEAVYGREENSWITCH_UP:
		getBoard()->updateGateList(NS_GREENGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), HEAVYGREENSWITCH_DOWN);
		break;
	case ORANGESWITCH_UP:
		getBoard()->updateGateList(NS_ORANGEGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), ORANGESWITCH_DOWN);
		break;
	case HEAVYORANGESWITCH_UP:
		getBoard()->updateGateList(NS_ORANGEGATE);
		getBoard()->setPrimaryTerrainAt(getY(), getX(), HEAVYORANGESWITCH_DOWN);
		break;
	}
}

void Block::move(direction_t direct, int distance, int startY, int startX)
{
	switch (direct) {
	case UP:
		setY(getY() - distance);
		setPrevDirection(UP);
		setDirection(UP);
		break;
	case DOWN:
		setY(getY() + distance);
		setPrevDirection(DOWN);
		setDirection(DOWN);
		break;
	case LEFT:
		setX(getX() - distance);
		setPrevDirection(LEFT);
		setDirection(LEFT);
		break;
	case RIGHT:
		setX(getX() + distance);
		setPrevDirection(RIGHT);
		setDirection(RIGHT);
		break;
	}
	getBoard()->addMoveableAt(getY(), getX(), this);
	getBoard()->removeMoveableAt(startY, startX, this);
	getBoard()->addToChangeList(getY(), getX());
	getBoard()->addToChangeList(startY, startX);
}
