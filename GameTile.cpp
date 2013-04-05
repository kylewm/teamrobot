// GameTile.cpp: implementation of the GameTile class.
//
//////////////////////////////////////////////////////////////////////

#include "GameTile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameTile::GameTile()
{
	GameTile(FLOOR);
}

GameTile::GameTile(terrain_t newType) {
	setPrimaryTerrain(newType);
	setSecondaryTerrain(newType);
	setTerrainExploding(false);
}

GameTile::~GameTile()
{
}

void GameTile::addMoveable(Moveable *obj) {
	moveableList.push_back(obj);
}

void GameTile::removeMoveable(Moveable *obj) {
	vector<Moveable*>::iterator i = moveableList.begin();
	for(i; i != moveableList.end(); ++i) {
		if(*i == obj) {
		moveableList.erase(i);
		return;
		}
	}
}

void GameTile::setPrimaryTerrain(terrain_t newType) {
	primaryTerrain = newType;
}

terrain_t GameTile::getPrimaryTerrain()
{
	return primaryTerrain;
}

void GameTile::setSecondaryTerrain(terrain_t newType) {
	secondaryTerrain = newType;
}

terrain_t GameTile::getSecondaryTerrain()
{
	return secondaryTerrain;
}

bool GameTile::getTerrainExploding()
{
	return terrainExploding;
}

void GameTile::setTerrainExploding(bool newVal)
{
	terrainExploding = newVal;
}

vector<Moveable*> GameTile::getMoveableList()
{
	return moveableList;
}
