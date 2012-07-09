// GameTile.h: interface for the GameTile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GAMETILE_H_
#define _GAMETILE_H_

/*#include <ClanLib/core.h>
#include <ClanLib/gui.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>*/
#include "team_robot.h"
#include "Moveable.h"
#include <vector>
using namespace std;

class Moveable;
class GameBoard;
class Terrain;

class GameTile  
{
public:
	vector<Moveable*> getMoveableList();
	void setTerrainExploding(bool newVal);
	bool getTerrainExploding();
	terrain_t getPrimaryTerrain();
	terrain_t getSecondaryTerrain();
	GameTile();
	GameTile(terrain_t);
	virtual ~GameTile();
	void addMoveable(Moveable *obj);
	void removeMoveable(Moveable *obj);
	void setPrimaryTerrain(terrain_t newType);
	void setSecondaryTerrain(terrain_t newType);
	//CL_Sprite *sprite;

private:
	terrain_t primaryTerrain;
	terrain_t secondaryTerrain;
	vector<Moveable*> moveableList;
	bool terrainExploding;
};

#endif
