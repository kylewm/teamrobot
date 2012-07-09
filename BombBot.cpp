// BombBot.cpp: implementation of the BombBot class.
//
//////////////////////////////////////////////////////////////////////

#include "BombBot.h"
#include "GameBoard.h"
#include "GameTile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BombBot::BombBot()
{

}

BombBot::BombBot(int inY, int inX, direction_t inDirection, 
	int inPrevY, int inPrevX, direction_t inPrevDirection, 
	GameBoard *inBoard, moveable_t inType, 
	bool inDeployedOnBoard,
	bool inSelected, bool inJustLaunched, bool newInTrain)
	: Moveable(inY, inX, inDirection, 
	inPrevY, inPrevX, inPrevDirection, 
	inBoard, inType, 
	inDeployedOnBoard,
	inSelected, inJustLaunched, newInTrain)
{
}

BombBot::~BombBot()
{

}

void BombBot::move()
{
	setPrevY(getY());
	setPrevX(getX());
	setPrevDirection(getDirection());

	Moveable::move(getDirection(), 1, getPrevY(), getPrevX());
}

void BombBot::collide()
{
	if(!getExploding()) {
		//Check for the situation that two moveable things are headed straight at each other
		//and pass by each other after move()
		GameTile *prevTile = getBoard()->getTileAt(getPrevY(), getPrevX());
		vector<Moveable*> prevML = prevTile->getMoveableList();
		
		vector<Moveable*>::iterator iter = prevML.begin();
		for(iter; iter != prevML.end(); ++iter) {
			if( ((*iter)->getPrevY() == getY()) &&
				((*iter)->getPrevX() == getX()) &&
				((*iter) != this)) {
				//then the weird situation has occured
				//this weird situation will be detected by this robot first
				//the other robot involved will not detect a weird situation,
				//but will react appropriately to the state of this robot after
				//this function
				
				setExploding(true);
				setExplodingDistance(0.0);
				setHeadOn(true);

				(*iter)->setHeadOn(true);
				(*iter)->setExploding(true);
				(*iter)->setExplodingDistance(0.0);

				if((*iter)->getInTrain()) {
					getBoard()->setExplodeAll(true);
				}

				return;
			}
		}
		
		
		GameTile *curTile = getBoard()->getTileAt(getY(), getX());
		vector<Moveable*> curML = curTile->getMoveableList();
		
		//If the moveableList is 1 or less, then no moveables to crash into, otherwise explode
		for(int i = 0; i < curML.size(); ++i) {
			if((curML.at(i) != this) && !(curML.at(i)->getHeadOn()) && curML.at(i)->getDeployedOnBoard()) {
				setExploding(true);
				setExplodingDistance(0.5);

				if(curML.at(i)->getInTrain()) {
					if(((getDirection() == UP) && (curML.at(i)->getDirection() == DOWN)) ||
						((getDirection() == DOWN) && (curML.at(i)->getDirection() == UP)) ||
						((getDirection() == LEFT) && (curML.at(i)->getDirection() == RIGHT)) ||
						((getDirection() == RIGHT) && (curML.at(i)->getDirection() == LEFT))) {
						//Then a head on collision, so destroy the whole train
						getBoard()->setExplodeAll(true);
					}
				}

				return;
			}
		}
		
		//Now check the terrain at this tile
		switch(curTile->getPrimaryTerrain()) {
		case WALL:
		case LASERABLE:
		case DRILLABLE:
			setExploding(true);
			setExplodingDistance(1.0);
			break;
		case NS_BLUEGATE:
		case NS_GREENGATE:
		case NS_REDGATE:
		case NS_ORANGEGATE:
		case EW_BLUEGATE:
		case EW_GREENGATE:
		case EW_REDGATE:
		case EW_ORANGEGATE:
			setFalling(true);
			break;
		case WATER:
			setDrowning(true);
			break;
		case PIT:
			setFalling(true);
			break;
		case BOMBABLE:
			getBoard()->explodeBombables(getY(), getX());
			setExploding(true);
			setExplodingDistance(1.0);
			break;
		case UPARROW: 
		case R_UPARROW:
			setDirection(UP);
			break;
		case DOWNARROW:
		case R_DOWNARROW:
			setDirection(DOWN);
			break;
		case LEFTARROW:
		case R_LEFTARROW:
			setDirection(LEFT);
			break;
		case RIGHTARROW:	 
		case R_RIGHTARROW:
			setDirection(RIGHT);
			break;
		case REDSWITCH_UP:
			getBoard()->updateGateList(NS_REDGATE);
			getBoard()->setPrimaryTerrainAt(getY(), getX(), REDSWITCH_DOWN);
			break;
		case BLUESWITCH_UP:
			getBoard()->updateGateList(NS_BLUEGATE);
			getBoard()->setPrimaryTerrainAt(getY(), getX(), BLUESWITCH_DOWN);
			break;
		case GREENSWITCH_UP:
			getBoard()->updateGateList(NS_GREENGATE);
			getBoard()->setPrimaryTerrainAt(getY(), getX(), GREENSWITCH_DOWN);
			break;
		case ORANGESWITCH_UP:
			getBoard()->updateGateList(NS_ORANGEGATE);
			getBoard()->setPrimaryTerrainAt(getY(), getX(), ORANGESWITCH_DOWN);
			break;
		case FINISH:
			setFinished(true);
			break;
		}
	}
}
