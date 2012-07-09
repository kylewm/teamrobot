// GameBoard.h: interface for the GameBoard class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include "team_robot.h"


#include <stdio.h>
#include <string>
#include <vector>
#include "Moveable.h"	// Added by ClassView

using namespace std;

class GameTile;
class Moveable;
class Block;
class Undeployed;

class GameBoard  
{
public:
	void addToLaunchBotList(Moveable *newBot);
	void addToLaunchDirectionList(direction_t newDirection);
	void addToLaunchBehaviorList(behavior_t newBehavior);
	int getBotsLeft();
	void setExplodeAll(bool newVal);
	string getLevelDescription();
	void removeFromDecoyList(int y, int x);
	vector<int> getDecoyList();
	void addToDecoyList(int y, int x);
	void explodeBombables(int y, int x);
	Moveable *getFrontBot();
	void addToMoveableListAt(vector<Moveable*>::iterator place, Moveable *newVal);
	void setGameState(gameState_t newVal);
	gameState_t getGameState();
	void launchBot(Moveable *theBot, behavior_t launchBehavior, direction_t launchDirection);
	void updateGateList(terrain_t gateType);
	GameTile *getTileAt(int y, int x);
	string getMapTitle();
	void setNumberOfBots(int newVal);
	void setSecondaryTerrainAt(int y, int x, terrain_t newVal);
	void setPrimaryTerrainAt(int y, int x, terrain_t newVal);
	vector<int> getChangeList();
	void clearChangeList();
	void addToChangeList(int y, int x);
	GameBoard();
	virtual ~GameBoard();
	bool loadBoard(const char* filename);
	void moveAll();
	void collideAll();
	void removeMoveableAt(int y, int x, Moveable *obj);
	void addMoveableAt(int y, int x, Moveable *obj);
	void nextTurn();
	void addToMoveableList(Moveable *obj);
	vector<Moveable*>::iterator removeFromMoveableList(Moveable *obj);
	void removeFromTrain(Moveable *rob);
	void setStartDirection(direction_t newVal);
	int getNumberOfBots();
	int getEarnedBots();
	bool getNewBot();
private:
	Moveable* getLaunchBot();
	behavior_t getLaunchBehavior();
	direction_t getLaunchDirection();
	vector<Moveable *> launchBotList;
	vector<direction_t> launchDirectionList;
	vector<behavior_t> launchBehaviorList;
	void explodeAllBots();
	void setLevelDescription(string newVal);
	string levelDescription;
	int botsLaunched;
	gameState_t gameState;
	void checkForEffects();
	void setMapTitle(string newVal);
	direction_t getStartDirection();
	void setStartY(int newVal);
	void setStartX(int newVal);
	int getStartY();
	int getStartX();
	direction_t startDirection;
	int numberOfBots;
	string mapTitle;
	int startY;
	int startX;
	void setTurnNumber(int newVal);
	void addToGateList(int y, int x);
	vector<int> gateList;
	vector<int> decoyList;
	moveable_t curBotType;
	void addToTrain(Moveable *rob);
//	behavior_t launchBehavior;
	bool launch;
//	direction_t launchDirection;
	GameTile *tiles[20][20];
	vector<Moveable*> moveableList;
	vector<Moveable*> train;
	vector<int> changeList;
	int turnNumber;
	int earnedBots;
	bool newBot;
	bool explodeAll;
	void setEarnedBots(int);
	void setNewBot(int);
};

#endif 