// GameBoard.cpp: implementation of the GameBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "GameBoard.h"
#include "GameTile.h"
#include "Moveable.h"
#include "Block.h"
#include "Undeployed.h"
#include "PushBot.h"
#include "CabooseBot.h"
#include "DrillBot.h"
#include "Swimbot.h"
#include "BombBot.h"
#include "TurnBot.h"
#include "WallCrawler.h"
#include "BridgeBot.h"
#include "Enemy.h"
#include "DecoyBot.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{
	changeList.~vector();
	gateList.~vector();
	mapTitle.~basic_string();
	moveableList.~vector();
	train.~vector();
	//decoyList.~vector();

	for(int i = 0; i < 20; ++i) {
		for(int j = 0; j < 20; ++j) {
			delete tiles[i][j];
		}
	}
}

// should probably be in its own levelreader sort of class
bool GameBoard::loadBoard(const char *filename) {
	FILE *fp;
	
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Could not load board: %s\n", filename);
		return false;
	}
	
	char temp[80];	
	if (fgets(temp, 80, fp) == NULL) {
		printf("Incorrect format for game board: %s\n", filename);
		return false;
	}

	setMapTitle(temp);

	if (fgets(temp, 4, fp) == NULL) {
		printf("Incorrect format for game board: %s\n", filename);
		return false;
	}

	setNumberOfBots(atoi(temp));

	if (fgets(temp, 4, fp) == NULL) {
		printf("Incorrect format for game board: %s\n", filename);
		return false;
	}

	setEarnedBots(atoi(temp));

	if (fgets(temp, 4, fp) == NULL) {
		printf("Incorrect format for game board: %s\n", filename);
		return false;
	}

	setNewBot(atoi(temp));

	char temp2[1000];	
	if (fgets(temp2, 1000, fp) == NULL) {
		printf("Incorrect format for game board: %s\n", filename);
		return false;
	}

	setLevelDescription(temp2);
	
	//This is temporary.  I just want to make sure that bots are added
	//to the map before enemies
	for(int i = 0; i < numberOfBots;  ++i) {
		Undeployed *newBot = new Undeployed(0, 0, NONE, 0, 0, NONE, this, 
			GENERICBOT, false, false, false, true);
		addToTrain(newBot);
		addToMoveableList(newBot);
	}
	
	CabooseBot *cb = new CabooseBot(0, 0, NONE, 0, 0, NONE, this, 
		CABOOSEBOT, false, false, false, true);
	addToTrain(cb);
	addToMoveableList(cb);
	
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 20; col++) {
			char inChar;
			Moveable *m;

			if ((inChar = fgetc(fp)) == NULL) {
				printf("Incorrect format for game board: %s\n", filename);
				return false;
			}
			switch(inChar) {
			case '.': 
				tiles[row][col] = new GameTile(FLOOR);
				break;
			case '0': 
				tiles[row][col] = new GameTile(WALL);
				break;
			case '1': 
				tiles[row][col] = new GameTile(BOMBABLE);
				break;
			case '2':
				tiles[row][col] = new GameTile(LASERABLE);
				break;
			case '3':
				m = new Block(row, col, DOWN, row, col, DOWN, this, BLOCK, true);
				tiles[row][col] = new GameTile(FLOOR);
				tiles[row][col]->addMoveable(m);
				addToMoveableListAt(moveableList.begin(), m);
				m->setDeployedOnBoard(true);
				break;
			case '4':
				tiles[row][col] = new GameTile(DRILLABLE);
				break;
			case '5':
				tiles[row][col] = new GameTile(WATER);
				break;
			case '6':
				tiles[row][col] = new GameTile(PIT);
				break;
			case 'r':
				tiles[row][col] = new GameTile(REDSWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'g':
				tiles[row][col] = new GameTile(GREENSWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'b':
				tiles[row][col] = new GameTile(BLUESWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'o':
				tiles[row][col] = new GameTile(ORANGESWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'q':
				tiles[row][col] = new GameTile(HEAVYREDSWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'w':
				tiles[row][col] = new GameTile(HEAVYGREENSWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'a':
				tiles[row][col] = new GameTile(HEAVYBLUESWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'z':
				tiles[row][col] = new GameTile(HEAVYORANGESWITCH_UP);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'R':
				tiles[row][col] = new GameTile(NS_REDGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'G':
				tiles[row][col] = new GameTile(NS_GREENGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'B':
				tiles[row][col] = new GameTile(NS_BLUEGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'O':
				tiles[row][col] = new GameTile(NS_ORANGEGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'Q':
				tiles[row][col] = new GameTile(EW_REDGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'W':
				tiles[row][col] = new GameTile(EW_GREENGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'A':
				tiles[row][col] = new GameTile(EW_BLUEGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case 'Z':
				tiles[row][col] = new GameTile(EW_ORANGEGATE);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				addToGateList(row, col);
				break;
			case '<':
				tiles[row][col] = new GameTile(LEFTARROW);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case '>':
				tiles[row][col] = new GameTile(RIGHTARROW);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case '^':
				tiles[row][col] = new GameTile(UPARROW);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 'v':
				tiles[row][col] = new GameTile(DOWNARROW);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case 's':
				tiles[row][col] = new GameTile(START);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				setStartX(col);
				setStartY(row);
				break;
			case 'f':
				tiles[row][col] = new GameTile(FINISH);
				tiles[row][col]->setSecondaryTerrain(FLOOR);
				break;
			case '{':
				m = new Enemy(row, col, LEFT, row, col, LEFT, this, ENEMY, true);
				tiles[row][col] = new GameTile(FLOOR);
				tiles[row][col]->addMoveable(m);
				addToMoveableList(m);
				m->setDeployedOnBoard(true);
				break;
			case '}':
				m = new Enemy(row, col, RIGHT, row, col, RIGHT, this, ENEMY, true);
				tiles[row][col] = new GameTile(FLOOR);
				tiles[row][col]->addMoveable(m);
				addToMoveableList(m);
				m->setDeployedOnBoard(true);
				break;
			case '[':
				m = new Enemy(row, col, UP, row, col, UP, this, ENEMY, true);
				tiles[row][col] = new GameTile(FLOOR);
				tiles[row][col]->addMoveable(m);
				addToMoveableList(m);
				m->setDeployedOnBoard(true);
				break;
			case ']':
				m = new Enemy(row, col, DOWN, row, col, DOWN, this, ENEMY, true);
				tiles[row][col] = new GameTile(FLOOR);
				tiles[row][col]->addMoveable(m);
				addToMoveableList(m);
				m->setDeployedOnBoard(true);
				break;
			default:
				fprintf(stderr, "Unknown terraintype: %c in game board: %s\n", inChar, filename);
				return false;
			}
		}
		if (fgetc(fp) != '\n') {
				fprintf(stderr, "Incorrect line-ending for game board: %s\n", filename);
				return false;
		}
	}

	turnNumber = 0;
	botsLaunched = 0;
	launch = false;
	explodeAll = false;
//	launchDirection = NONE;
	startDirection = NONE;
	gameState = NOTFINISHED;

	for(i = 0; i <= numberOfBots; ++i) {
		train.at(i)->setX(startX);
		train.at(i)->setY(startY);
		train.at(i)->setPrevX(startX);
		train.at(i)->setPrevY(startY);

	}

	train.at(0)->setSelected(true);

	return true;
}

void GameBoard::moveAll() {
	for (int i = 0; i < moveableList.size(); i++) {
		Moveable *temp = moveableList.at(i);
		temp->setMoved(false);
		temp->setUTurn(false);
		if(temp->getType() == ENEMY) { 
			((Enemy *) temp)->setTurned(false);
			if(!decoyList.empty()) {
				//directionBasedOnDecoys chooses the direction to the closest decoy
				direction_t tempDirection = ((Enemy *) temp)->directionBasedOnDecoys();
				temp->setDirection(tempDirection);
				temp->setPrevDirection(tempDirection);
			}
		}
	}

	for (i = 0; i < moveableList.size(); i++) {
		Moveable *temp = moveableList.at(i);
		if(temp->getDeployedOnBoard()) {
			temp->move();
		}
	}
}

void GameBoard::collideAll() {
	for (int i = 0; i < moveableList.size(); i++) {
		Moveable *temp = moveableList.at(i);
		temp->setHeadOn(false);
	}

	for (i = 0; i < moveableList.size(); i++) {
		Moveable *temp = moveableList.at(i);
		if(temp->getDeployedOnBoard()) {
			temp->collide();
		}
	}
}

void GameBoard::removeMoveableAt(int y, int x, Moveable *obj) {
	tiles[y][x]->removeMoveable(obj);
}

void GameBoard::addMoveableAt(int y, int x, Moveable *obj) {
	tiles[y][x]->addMoveable(obj);
}

void GameBoard::nextTurn() {
	checkForEffects();

	if((botsLaunched <= numberOfBots) && (startDirection != NONE)) {
		vector<Moveable*>::iterator iter = train.begin();

		//find the next undeployed bot
		for(iter; iter != train.end(); ++iter) {
			if(!(*iter)->getDeployedOnBoard()) {
				break;
			}
		}

		if(!(*iter)->getExploding()) {
			(*iter)->setDirection(startDirection);
			(*iter)->setDeployedOnBoard(true);
			++botsLaunched;
		}
	}
	
	for(int i = 0; i < launchBotList.size(); ++i) {
		if(/*launch && */!((launchBotList.at(i)->getY() == startY) && (launchBotList.at(i)->getX() == startX))) {
			//Then launch the bot and reduce i, so it doesn't skip over the next bot
			launchBot(launchBotList.at(i), launchBehaviorList.at(i), launchDirectionList.at(i));

			//Stupid hack to get an iterator where we need to erase
			vector<behavior_t>::iterator tempIter1 = launchBehaviorList.begin();
			vector<direction_t>::iterator tempIter2 = launchDirectionList.begin();
			vector<Moveable*>::iterator tempIter3 = launchBotList.begin();

			for(int j = 0; j < i; ++j) {
				tempIter1++;
				tempIter2++;
				tempIter3++;
			}

			launchBehaviorList.erase(tempIter1);
			launchDirectionList.erase(tempIter2);
			launchBotList.erase(tempIter3);
			--i;

		}
	}

	moveAll();
	collideAll();

	if(explodeAll) {
		explodeAllBots();
	}


	++turnNumber;
}


//DEL void GameBoard::setLaunchDirection(direction_t newVal)
//DEL {
//DEL 	if(launchDirection == NONE) {
//DEL 		setStartDirection(newVal);
//DEL 	}
//DEL 	launchDirection = newVal;
//DEL }

//DEL void GameBoard::setLaunchBehavior(behavior_t newVal)
//DEL {
//DEL 	launchBehavior = newVal;
//DEL }

void GameBoard::addToMoveableList(Moveable *obj) {
	moveableList.push_back(obj);
}

vector<Moveable*>::iterator GameBoard::removeFromMoveableList(Moveable *obj) {
	vector<Moveable*>::iterator i = moveableList.begin();
	for(i; i != moveableList.end(); ++i) {
		if(*i == obj) {
		moveableList.erase(i);
		return i;
		}
	}
	return i;
}

void GameBoard::setTurnNumber(int newVal)
{
	turnNumber = newVal;
}

void GameBoard::addToChangeList(int y, int x)
{
	vector<int>::iterator iter = changeList.begin();

	for(iter; iter != changeList.end(); iter += 2) {
		if((*iter == y) && (*(iter + 1) == x)) {
			return;
		}
	}
	changeList.push_back(y);
	changeList.push_back(x);
}

void GameBoard::clearChangeList()
{
	changeList.clear();
}

vector<int> GameBoard::getChangeList()
{
	return changeList;
}

void GameBoard::addToTrain(Moveable *rob)
{
	train.push_back(rob);
}

void GameBoard::removeFromTrain(Moveable *rob)
{
	vector<Moveable*>::iterator i = train.begin();
	for(i; i != train.end(); ++i) {
		if(*i == rob) {
			(*i)->setSelected(false);
			(*i)->setInTrain(false);
			train.erase(i);
			//reset the selected robot in case the lead robot just got
			//removed
			if(!train.empty()) {
				train.at(0)->setSelected(true);
			}
			return;
		}
	}
}


void GameBoard::setPrimaryTerrainAt(int y, int x, terrain_t newVal)
{
	tiles[y][x]->setPrimaryTerrain(newVal);
}

void GameBoard::addToGateList(int y, int x)
{
	gateList.push_back(y);
	gateList.push_back(x);
}

void GameBoard::setSecondaryTerrainAt(int y, int x, terrain_t newVal)
{
	tiles[y][x]->setSecondaryTerrain(newVal);
}

int GameBoard::getStartX()
{
	return startX;
}

int GameBoard::getStartY()
{
	return startY;
}

void GameBoard::setStartX(int newVal)
{
	startX = newVal;
}

void GameBoard::setStartY(int newVal)
{
	startY = newVal;
}

direction_t GameBoard::getStartDirection()
{
	return startDirection;
}

void GameBoard::setStartDirection(direction_t newVal)
{
	startDirection = newVal;
}

int GameBoard::getNumberOfBots()
{
	return numberOfBots;
}

void GameBoard::setNumberOfBots(int newVal)
{
	numberOfBots = newVal;
}

string GameBoard::getMapTitle()
{
	return mapTitle;
}

void GameBoard::setMapTitle(string newVal)
{
	mapTitle = newVal;
}

GameTile *GameBoard::getTileAt(int y, int x)
{
	return tiles[y][x];
}

void GameBoard::updateGateList(terrain_t gateType)
{
	vector<int>::iterator iter = gateList.begin();

	for(iter; iter != gateList.end();) {
		//This is whether the gate should remain or not
		bool saveGate = true;
		terrain_t curTer = (tiles[*iter][*(iter + 1)])->getPrimaryTerrain();

		if((curTer == gateType) ||
			(curTer == (gateType + 1))) {
			setPrimaryTerrainAt(*iter, *(iter + 1), FLOOR);
			saveGate = false;
		}

		if(saveGate) {
			//then not the right color, so keep the gate on the gateList
			iter += 2;
		} else {
			//otherwise no status changed, so take the gate off the gateList
			addToChangeList(*iter, *(iter + 1));
			iter = gateList.erase(iter, (iter + 2));
		}
	}
}

void GameBoard::checkForEffects()
{
	vector<int>::iterator iter = changeList.begin();

	for(iter; iter != changeList.end();) {
		//this boolean is used to tell whether we should remove
		//this square from the changeList or not
		bool saveSquare = false;

		//get the tile that recently changed
		GameTile *theTile = tiles[*(iter)][*(iter + 1)];

		//Take care of exploding terrain at that tile
		if(theTile->getTerrainExploding()) {
			theTile->setTerrainExploding(false);
			saveSquare = true;
		}

		//Check for exploding/drowning/falling/finished moveables at the square
		vector<Moveable*> theML = theTile->getMoveableList();
		vector<Moveable*>::iterator mlIter = theML.begin();

		for(mlIter; mlIter != theML.end(); ++mlIter) {
			if((*mlIter)->getType() == BLOCK) {
				if((*mlIter)->getDrowning() || (*mlIter)->getFalling()) {
					(*mlIter)->setDeployedOnBoard(false);
					setPrimaryTerrainAt((*mlIter)->getY(), (*mlIter)->getX(), FLOOR_LAVA);
					removeFromMoveableList(*mlIter);
					removeMoveableAt(*iter, *(iter + 1), *mlIter);
					//delete *mlIter;
					saveSquare = true;
				}
				if((*mlIter)->getExploding()) {
					(*mlIter)->setDeployedOnBoard(false);
					removeFromMoveableList(*mlIter);
					removeMoveableAt(*iter, *(iter + 1), *mlIter);
					//delete *mlIter;
					saveSquare = true;
				}
			}
			else {
				if((*mlIter)->getDrowning() || (*mlIter)->getExploding() ||
					(*mlIter)->getFalling() || (*mlIter)->getFinished()) {
					if((*mlIter)->getType() == DECOYBOT) {
						removeFromDecoyList((*mlIter)->getY(), (*mlIter)->getX());
					}
					if(((*mlIter)->getType() == CABOOSEBOT) && !(*mlIter)->getFinished()) {
						setGameState(LOSE);
					}
					(*mlIter)->setDeployedOnBoard(false);
					removeFromTrain(*mlIter);
					removeFromMoveableList(*mlIter);
					removeMoveableAt(*iter, *(iter + 1), *mlIter);
					//delete *mlIter;
					saveSquare = true;
				}
				if((*mlIter)->getJustLaunched()) {
					(*mlIter)->setJustLaunched(false);
				}
			}
		}

		if(saveSquare) {
			//then something changed, so keep the square on the changeList
			iter += 2;
		} else {
			//otherwise no status changed, so take the square off the changeList
			iter = changeList.erase(iter, iter + 2);
		}
	}
}

void GameBoard::launchBot(Moveable *theBot, behavior_t launchBehavior, direction_t launchDirection)
{
	if((theBot != NULL) && (theBot->getType() != CABOOSEBOT) && !theBot->getBeenLaunched()) {
		Moveable *newBot;
		
		switch(theBot->getType()) {
		case GENERICBOT:
			newBot = new Undeployed(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				GENERICBOT, true, false, true, false);
			newBot->setBeenLaunched(true);
			break;
		case DRILLBOT:
			newBot = new DrillBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				DRILLBOT, true, false, true, false);
			newBot->setBeenLaunched(true);
			break;
		case PUSHBOT: 
			newBot = new PushBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				PUSHBOT, true, false, true, false);	
			newBot->setBeenLaunched(true);
			break;
		case DECOYBOT: 
			newBot = new DecoyBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				DECOYBOT, true, false, true, false);
			newBot->setBeenLaunched(true);
			break;
		case BOMBBOT:
			newBot = new BombBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				BOMBBOT, true, false, true, false);
			newBot->setBeenLaunched(true);
			break;
		case TURNBOT:
			newBot = new TurnBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				TURNBOT, true, false, true, false, launchBehavior);
			newBot->setBeenLaunched(true);
			break;
		case WALLCRAWLER:
			newBot = new WallCrawler(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				WALLCRAWLER, true, false, true, false, launchBehavior);
			newBot->setBeenLaunched(true);
			break;
		case SWIMBOT:
			newBot = new SwimBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				SWIMBOT, true, false, true, false);
			newBot->setBeenLaunched(true);
			break;
		case BRIDGEBOT:
			newBot = new BridgeBot(theBot->getY(), theBot->getX(), launchDirection, theBot->getPrevY(), 
				theBot->getPrevY(), theBot->getPrevDirection(), this, 
				BRIDGEBOT, true, false, true, false);
			newBot->setBeenLaunched(true);
			break;
		case REDIRECTBOT:
			switch(launchDirection) {
			case UP:
				setPrimaryTerrainAt(theBot->getY(), theBot->getX(), R_UPARROW);
				tiles[theBot->getY()][theBot->getX()]->setSecondaryTerrain(FLOOR);
				break;
			case DOWN:
				setPrimaryTerrainAt(theBot->getY(), theBot->getX(), R_DOWNARROW);
				tiles[theBot->getY()][theBot->getX()]->setSecondaryTerrain(FLOOR);
				break;
			case LEFT:
				setPrimaryTerrainAt(theBot->getY(), theBot->getX(), R_LEFTARROW);
				tiles[theBot->getY()][theBot->getX()]->setSecondaryTerrain(FLOOR);
				break;
			case RIGHT:
				setPrimaryTerrainAt(theBot->getY(), theBot->getX(), R_RIGHTARROW);
				tiles[theBot->getY()][theBot->getX()]->setSecondaryTerrain(FLOOR);
				break;
			}
			break;
			
		}
		
		vector<Moveable*>::iterator insertPlace;
		
		theBot->setDeployedOnBoard(false);
		removeFromTrain(theBot);
		insertPlace = removeFromMoveableList(theBot);
		removeMoveableAt(theBot->getY(), theBot->getX(), theBot);	
		
		
		//If it's a moveable bot, make sure the board knows about it
		if(theBot->getType() != REDIRECTBOT) {
			addMoveableAt(theBot->getY(), theBot->getX(), newBot);
			addToMoveableListAt(insertPlace, newBot);
		}
		delete theBot;
		//launch = false;
	}
	
	//launch = false;
}

gameState_t GameBoard::getGameState()
{
	return gameState;
}

void GameBoard::setGameState(gameState_t newVal)
{
	gameState = newVal;
}

void GameBoard::addToMoveableListAt(vector<Moveable*>::iterator place, Moveable *newVal)
{
	moveableList.insert(place, newVal);
}

Moveable *GameBoard::getFrontBot()
{
	return train.at(0);
}

void GameBoard::explodeBombables(int y, int x)
{
	if(tiles[y][x]->getPrimaryTerrain() == BOMBABLE) {
		tiles[y][x]->setPrimaryTerrain(FLOOR);
		tiles[y][x]->setTerrainExploding(true);
		addToChangeList(y, x);
		explodeBombables(y + 1, x);
		explodeBombables(y - 1, x);
		explodeBombables(y, x - 1);
		explodeBombables(y, x + 1);
	}
}

void GameBoard::addToDecoyList(int y, int x)
{
	decoyList.push_back(y);
	decoyList.push_back(x);
}

vector<int> GameBoard::getDecoyList()
{
	return decoyList;
}

void GameBoard::removeFromDecoyList(int y, int x)
{
	vector<int>::iterator iter = decoyList.begin();

	for(iter; iter != decoyList.end();) {
		if((*iter == y) && (*(iter + 1) == x)) {
			decoyList.erase(iter, (iter + 2));
			return;
		}
		else {
			iter += 2;
		}
	}
}

int GameBoard::getEarnedBots() {
	return earnedBots;
}

void GameBoard::setEarnedBots(int earnedBots) {
	this->earnedBots = earnedBots;
}

bool GameBoard::getNewBot() {
	return newBot;
}

void GameBoard::setNewBot(int num) {
	if (num == 1) {
		this->newBot = true;
	}
	else {
		this->newBot = false;
	}
}

void GameBoard::setLevelDescription(string newVal)
{
	levelDescription = newVal;
}

string GameBoard::getLevelDescription()
{
	return levelDescription;
}

void GameBoard::explodeAllBots()
{
	for (int i = 0; i < train.size(); i++) {
		Moveable *temp = train.at(i);
		temp->setExploding(true);
	}

	setGameState(LOSE);
}

void GameBoard::setExplodeAll(bool newVal)
{
	explodeAll = true;
}

int GameBoard::getBotsLeft()
{
	int ret = train.size() - 1;

	if(ret < 0) {
		ret = 0;
	}

	return ret;
}


void GameBoard::addToLaunchBehaviorList(behavior_t newBehavior)
{
	//First check to see if this is the first arrow clicked
	//If so, do nothing
	if(startDirection != NONE) {
		if(train.size() > 1) {
			launchBehaviorList.push_back(newBehavior);
			train.at(0)->setBehavior(newBehavior);
		}
	}
}

void GameBoard::addToLaunchDirectionList(direction_t newDirection)
{
	//The first arrow click sets startDirection.  Everything after that launches bots.
	if(startDirection == NONE) {
		setStartDirection(newDirection);
	}
	else {
		if(train.size() > 1) {
			addToLaunchBotList(train.at(0));
			if(train.at(0)->getDeployedOnBoard()) {
				removeFromTrain(train.at(0));
			}
			launchDirectionList.push_back(newDirection);
		}
	}
}

direction_t GameBoard::getLaunchDirection()
{
	return launchDirectionList.at(0);;
}

behavior_t GameBoard::getLaunchBehavior()
{
	return launchBehaviorList.at(0);
}

Moveable* GameBoard::getLaunchBot()
{
	return launchBotList.at(0);
}

void GameBoard::addToLaunchBotList(Moveable *newBot)
{
	launchBotList.push_back(newBot);
}
