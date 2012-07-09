// Enemy.cpp: implementation of the Enemy class.
//
//////////////////////////////////////////////////////////////////////

#include "Enemy.h"
#include "GameBoard.h"
#include "GameTile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Enemy::Enemy()
{
	
}

Enemy::Enemy(int inY, int inX, direction_t inDirection, 
			 int inPrevY, int inPrevX, direction_t inPrevDirection, 
			 GameBoard *inBoard, moveable_t inType, 
			 bool inDeployedOnBoard)
			 : Moveable(inY, inX, inDirection, 
			 inPrevY, inPrevX, inPrevDirection, 
			 inBoard, inType, 
			 inDeployedOnBoard)
{
	turned = false;
}

Enemy::~Enemy()
{
	
}

void Enemy::collide()
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
				
				if((*iter)->getType() == BOMBBOT) {
					setExploding(true);
					setExplodingDistance(0.0);
				}

				setHeadOn(true);
				(*iter)->setHeadOn(true);

				if((*iter)->getType() != ENEMY) {
					(*iter)->setExploding(true);
					(*iter)->setExplodingDistance(0.0);
				}

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
			if((curML.at(i) != this) && !(curML.at(i)->getHeadOn())
				&& curML.at(i)->getDeployedOnBoard()) {
				if(curML.at(i)->getType() == BOMBBOT) {
					setExploding(true);
					setExplodingDistance(0.5);
				}

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
		}
	}
}

void Enemy::move()
{
	if(!getUTurn()  && !getMoved()) {
		setPrevY(getY());
		setPrevX(getX());
		
		//First we need to see if there are any decoys on the board
		if(getBoard()->getDecoyList().empty()) {
			setPrevDirection(getDirection());
			//If decoyList is empty, move like a 180 degree turnbot
			GameTile *oneAhead;
			GameTile *twoAhead;
			bool skipTA = false;
			
			switch(getDirection()) {
			case UP:
				oneAhead = getBoard()->getTileAt((getY() - 1), getX());
				if((getY() - 2) < 0) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt((getY() - 2), getX());
				}
				break;
			case DOWN:
				oneAhead = getBoard()->getTileAt((getY() + 1), getX());
				if((getY() + 2) > 19) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt((getY() + 2), getX());
				}
				break;
			case LEFT:
				oneAhead = getBoard()->getTileAt(getY(), (getX() - 1));
				if((getX() - 2) < 0) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt(getY(), (getX() - 2));
				}
				break;
			case RIGHT:
				oneAhead = getBoard()->getTileAt(getY(), (getX() + 1));
				if((getX() + 2) > 19) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt(getY(), (getX() + 2));
				}
				break;
			}

			//Based on what's ahead, make the appropriate move
			bool blockAhead = false;
			bool enemyAhead = false;
			vector<Moveable*> oAML = oneAhead->getMoveableList();
			vector<Moveable*>::iterator iter = oAML.begin();
			
			for(iter; iter != oAML.end(); ++iter) {
				if((*iter)->getType() == BLOCK) {
					blockAhead = true;
				}
				if((*iter)->getType() == ENEMY) {
					if((!(*iter)->getMoved()) && (!(*iter)->getUTurn()) && (!((Enemy *) (*iter))->getTurned())) {
						switch(getDirection()) {
						case UP:
							if((*iter)->getDirection() == DOWN) {
								(*iter)->setDirection(UP);
							}
							break;
						case DOWN:
							if((*iter)->getDirection() == UP) {
								(*iter)->setDirection(DOWN);
							}
							break;
						case LEFT:
							if((*iter)->getDirection() == RIGHT) {
								(*iter)->setDirection(LEFT);
							}
							break;
						case RIGHT:
							if((*iter)->getDirection() == LEFT) {
								(*iter)->setDirection(RIGHT);
								
							}
							break;
						}
						(*iter)->move();
						move();
						return;
					}
					else {
						enemyAhead = true;
					}
				}
			}

			if(blockAhead || enemyAhead || (oneAhead->getPrimaryTerrain() == WALL) ||
				(oneAhead->getPrimaryTerrain() == BOMBABLE) ||
				(oneAhead->getPrimaryTerrain() == LASERABLE) ||
				(oneAhead->getPrimaryTerrain() == DRILLABLE)) {
				skipTA = true;
			}
			
			if(!skipTA) {
				vector<Moveable*> tAML = twoAhead->getMoveableList();
				iter = tAML.begin();
				bool blockTA = false;
				for(iter; iter != tAML.end(); ++iter) {
					if((*iter)->getType() == BLOCK) {
						blockTA = true;
					}
					if(((*iter)->getType() == ENEMY) && ((*iter)->getMoved() == false)) {
						switch(getDirection()) {
						case UP:
							if((*iter)->getDirection() == DOWN) {
								(*iter)->setDirection(UP);
								setDirection(DOWN);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						case DOWN:
							if((*iter)->getDirection() == UP) {
								(*iter)->setDirection(DOWN);
								setDirection(UP);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						case LEFT:
							if((*iter)->getDirection() == RIGHT) {
								(*iter)->setDirection(LEFT);
								setDirection(RIGHT);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						case RIGHT:
							if((*iter)->getDirection() == LEFT) {
								(*iter)->setDirection(RIGHT);	
								setDirection(LEFT);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						}
					}
				}

				if((blockTA || (twoAhead->getPrimaryTerrain() == WALL) ||
					(twoAhead->getPrimaryTerrain() == BOMBABLE) ||
					(twoAhead->getPrimaryTerrain() == LASERABLE) ||
					(twoAhead->getPrimaryTerrain() == DRILLABLE))
					&& enemyAhead) {
					blockAhead = true;
				}
			}
			
			if(enemyAhead) {
				setMoved(true);
				return;
			}
			if(blockAhead || (oneAhead->getPrimaryTerrain() == WALL) ||
				(oneAhead->getPrimaryTerrain() == BOMBABLE) ||
				(oneAhead->getPrimaryTerrain() == LASERABLE) ||
				(oneAhead->getPrimaryTerrain() == DRILLABLE)) {
				//If it's something solid, then turn and call move again
				switch(getDirection()) {
				case UP:
					setDirection(DOWN);
					//setPrevDirection(DOWN);
					break;
				case DOWN:
					setDirection(UP);
					//setPrevDirection(UP);
					break;
				case LEFT:
					setDirection(RIGHT);
					//setPrevDirection(RIGHT);
					break;
				case RIGHT:
					setDirection(LEFT);
					//setPrevDirection(LEFT);
					break;
				}
				
				if(!getTurned()) {
					setTurned(true);
					move();		
					return;
				}
				else {
					return;
				}
			}
			else {
				//Otherwise just move straight ahead
				Moveable::move(getDirection(), 1, getPrevY(), getPrevX());
				setMoved(true);
			}
		}
		else {
			
			//Otherwise we're being attracted to a decoy
			
			GameTile *oneAhead;
			GameTile *twoAhead;
			bool skipTA = false;
			
			switch(getDirection()) {
			case UP:
				oneAhead = getBoard()->getTileAt((getY() - 1), getX());
				if((getY() - 2) < 0) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt((getY() - 2), getX());
				}
				break;
			case DOWN:
				oneAhead = getBoard()->getTileAt((getY() + 1), getX());
				if((getY() + 2) > 19) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt((getY() + 2), getX());
				}
				break;
			case LEFT:
				oneAhead = getBoard()->getTileAt(getY(), (getX() - 1));
				if((getX() - 2) < 0) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt(getY(), (getX() - 2));
				}
				break;
			case RIGHT:
				oneAhead = getBoard()->getTileAt(getY(), (getX() + 1));
				if((getX() + 2) > 19) {
					skipTA = true;
				}
				else {
					twoAhead = getBoard()->getTileAt(getY(), (getX() + 2));
				}
				break;
			}
			//Based on what's ahead, make the appropriate move
			bool blockAhead = false;
			bool enemyAhead = false;
			vector<Moveable*> oAML = oneAhead->getMoveableList();
			vector<Moveable*>::iterator iter = oAML.begin();
			
			for(iter; iter != oAML.end(); ++iter) {
				if((*iter)->getType() == BLOCK) {
					blockAhead = true;
				}
				if((*iter)->getType() == ENEMY) {
					if((!(*iter)->getMoved()) && (!(*iter)->getUTurn())) {
						switch(getDirection()) {
						case UP:
							if((*iter)->getDirection() == DOWN) {
								(*iter)->setDirection(UP);
							}
							break;
						case DOWN:
							if((*iter)->getDirection() == UP) {
								(*iter)->setDirection(DOWN);
							}
							break;
						case LEFT:
							if((*iter)->getDirection() == RIGHT) {
								(*iter)->setDirection(LEFT);
							}
							break;
						case RIGHT:
							if((*iter)->getDirection() == LEFT) {
								(*iter)->setDirection(RIGHT);
								
							}
							break;
						}
						(*iter)->move();
						move();
						return;
					}
					else {
						enemyAhead = true;
					}
				}
			}
			
			if(blockAhead || enemyAhead || (oneAhead->getPrimaryTerrain() == WALL) ||
				(oneAhead->getPrimaryTerrain() == BOMBABLE) ||
				(oneAhead->getPrimaryTerrain() == LASERABLE) ||
				(oneAhead->getPrimaryTerrain() == DRILLABLE)) {
				skipTA = true;
			}
			
			if(!skipTA) {
				vector<Moveable*> tAML = twoAhead->getMoveableList();
				iter = tAML.begin();
				bool blockTA = false;
				for(iter; iter != tAML.end(); ++iter) {
					if((*iter)->getType() == BLOCK) {
						blockTA = true;
					}
					if(((*iter)->getType() == ENEMY) && ((*iter)->getMoved() == false)) {
						switch(getDirection()) {
						case UP:
							if((*iter)->getDirection() == DOWN) {
								(*iter)->setDirection(UP);
								setDirection(DOWN);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						case DOWN:
							if((*iter)->getDirection() == UP) {
								(*iter)->setDirection(DOWN);
								setDirection(UP);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						case LEFT:
							if((*iter)->getDirection() == RIGHT) {
								(*iter)->setDirection(LEFT);
								setDirection(RIGHT);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						case RIGHT:
							if((*iter)->getDirection() == LEFT) {
								(*iter)->setDirection(RIGHT);	
								setDirection(LEFT);
								(*iter)->setUTurn(true);
								(*iter)->setMoved(true);
								setUTurn(true);
								setMoved(true);
								if(oAML.size() == 1) {
									if(oAML.at(0)->getType() != ENEMY) {
										oAML.at(0)->setExploding(true);
										oAML.at(0)->setExplodingDistance(0.5);
									}
								}
								return;
							}
							break;
						}
						
						return;
					}
				}
				
				if((blockTA || (twoAhead->getPrimaryTerrain() == WALL) ||
					(twoAhead->getPrimaryTerrain() == BOMBABLE) ||
					(twoAhead->getPrimaryTerrain() == LASERABLE) ||
					(twoAhead->getPrimaryTerrain() == DRILLABLE))
					&& enemyAhead) {
					blockAhead = true;
				}
			}
			
			if(blockAhead || enemyAhead || (oneAhead->getPrimaryTerrain() == WALL) ||
				(oneAhead->getPrimaryTerrain() == BOMBABLE) ||
				(oneAhead->getPrimaryTerrain() == LASERABLE) ||
				(oneAhead->getPrimaryTerrain() == DRILLABLE)) {
				//Don't move
				setMoved(true);
				return;
			}
			else {
				//Otherwise just move straight ahead
				Moveable::move(getDirection(), 1, getPrevY(), getPrevX());
				setMoved(true);
			}			
		}
	}
}

direction_t Enemy::directionBasedOnDecoys()
{
	//First, find the closest decoy.  If two or more are equidistant
	//chose the one that was placed first
	vector<int> temp = getBoard()->getDecoyList();
	
	//These variables keep track of where the closest decoy is
	//They are initialized to nonsense variables
	int xDiff = 50;
	int yDiff = 50;
	int closestDistance = 50;
	
	for(int i = 0; i < temp.size(); i += 2) {
		int thisYDiff = temp.at(i) - getY();
		int thisXDiff = temp.at(i + 1) - getX();
		int thisDistance = (abs(thisYDiff) + abs(thisXDiff));
		
		if(thisDistance < closestDistance) {
			closestDistance = thisDistance;
			xDiff = thisXDiff;
			yDiff = thisYDiff;
		}
	}
	
	//Now the complicated logic of mapping a decoy direction to a movement
	//direction
	if((yDiff < 0) && (xDiff < 0)) {
		switch(getPrevDirection()) {
		case UP:
		case DOWN:
			return LEFT;
			break;
		case LEFT:
		case RIGHT:
			return UP;
			break;
		default:
			return NONE;
		}
	}
	else if((yDiff < 0) && (xDiff == 0)) {
		return UP;
	}
	else if((yDiff < 0) && (xDiff > 0)) {
		switch(getPrevDirection()) {
		case UP:
		case DOWN:
			return RIGHT;
			break;
		case LEFT:
		case RIGHT:
			return UP;
			break;
		default:
			return NONE;
		}
	}
	else if((yDiff == 0) && (xDiff < 0)) {
		return LEFT;
	}
	else if((yDiff == 0) && (xDiff > 0)) {
		return RIGHT;
	}
	else if((yDiff > 0) && (xDiff < 0)) {
		switch(getPrevDirection()) {
		case UP:
		case DOWN:
			return LEFT;
			break;
		case LEFT:
		case RIGHT:
			return DOWN;
			break;
		default:
			return NONE;
		}
	}
	else if((yDiff > 0) && (xDiff == 0)) {
		return DOWN;
	}
	else if((yDiff > 0) && (xDiff > 0)) {
		switch(getPrevDirection()) {
		case UP:
		case DOWN:
			return RIGHT;
			break;
		case LEFT:
		case RIGHT:
			return DOWN;
			break;
		default:
			return NONE;
		}
	}
	else {
		return getPrevDirection();
	}
}

void Enemy::setTurned(bool newVal)
{
	turned = newVal;
}

bool Enemy::getTurned()
{
	return turned;
}
