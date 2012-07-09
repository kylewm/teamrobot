// GameDisplay.h: interface for the GameDisplay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(GAMEDISPLAY_H)
#define GAMEDISPLAY_H

#include <ClanLib/core.h>
#include <ClanLib/gui.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <vector>
#include "team_robot.h"
#include "GameBoard.h"
#include "GameTile.h"
#include "Moveable.h"

class GameUI;

class GameDisplay  
{
public:
	GameDisplay(GameUI*);
	virtual ~GameDisplay();
	void initLevel(int);
	gameState_t show(bool);

	int begin_time;
	int ctr;
	int time1;
	int time2;
	int time3;
	int time4;
	int time_ctr;

	GameBoard *myBoard;

	// movables
	CL_Surface *block;
	CL_Surface *genericbot;
	CL_Surface *caboosebot;
	CL_Surface *bridgebot;
	CL_Surface *arrowbot;
	CL_Surface *drillbot;
	CL_Surface *pushbot;
	CL_Surface *decoybot;
	CL_Surface *bombbot;
	CL_Surface *turnbot_left;
	CL_Surface *turnbot_right;
	CL_Surface *wallcrawler_left;
	CL_Surface *wallcrawler_right;
	CL_Surface *swimbot;
	CL_Surface *swimbotUnderwater;
	CL_Surface *enemy;

private:
	float cur_loc;
	int x_start;
	int y_start;
	bool anim_backwards;
	
	GameUI *myUI;

	// terrain
	CL_Surface *floor;
	CL_Surface *floorlava;
	CL_Surface *wall;
	CL_Surface *bombable;
	CL_Surface *laserable;
	CL_Surface *water;
	CL_Surface *splash;
	CL_Surface *pit;
	CL_Surface *ns_bridge;
	CL_Surface *ew_bridge;
	CL_Surface *drillable;
	CL_Surface *up_arrow;
	CL_Surface *down_arrow;
	CL_Surface *left_arrow;
	CL_Surface *right_arrow;
	CL_Surface *red_switch_up;
	CL_Surface *red_switch_down;
	CL_Surface *red_switch_up_h;
	CL_Surface *red_switch_down_h;
	CL_Surface *ns_red_gate;
	CL_Surface *ew_red_gate;
	CL_Surface *blue_switch_up;
	CL_Surface *blue_switch_down;
	CL_Surface *blue_switch_up_h;
	CL_Surface *blue_switch_down_h;
	CL_Surface *ns_blue_gate;
	CL_Surface *ew_blue_gate;
	CL_Surface *green_switch_up;
	CL_Surface *green_switch_down;
	CL_Surface *green_switch_up_h;
	CL_Surface *green_switch_down_h;
	CL_Surface *ns_green_gate;
	CL_Surface *ew_green_gate;
	CL_Surface *orange_switch_up;
	CL_Surface *orange_switch_down;
	CL_Surface *orange_switch_up_h;
	CL_Surface *orange_switch_down_h;
	CL_Surface *ns_orange_gate;
	CL_Surface *ew_orange_gate;
	CL_Surface *start00;
	CL_Surface *start05;
	CL_Surface *start10;
	CL_Surface *start15;
	CL_Surface *start20;
	CL_Surface *start25;
	CL_Surface *start30;
	CL_Surface *start35;
	CL_Surface *start40;
	CL_Surface *start45;
	CL_Surface *start50;
	CL_Surface *start55;
	CL_Surface *start60;
	CL_Surface *finish00;
	CL_Surface *finish05;
	CL_Surface *finish10;
	CL_Surface *finish15;
	CL_Surface *finish20;
	CL_Surface *finish25;
	CL_Surface *finish30;
	CL_Surface *finish35;
	CL_Surface *finish40;
	CL_Surface *finish45;
	CL_Surface *finish50;
	CL_Surface *finish55;
	CL_Surface *finish60;
	CL_Surface *selected;
	CL_Surface *in_train;
	CL_Surface *explosion1;
	CL_Surface *explosion2;
	CL_Surface *explosion3;
	CL_Surface *explosion4;
	CL_Surface *explosion5;
	CL_Surface *explosion6;
	CL_Surface *explosion7;
	CL_Surface *explosion8;
	CL_Surface *explosion9;
	CL_Surface *explosion10;
	CL_Surface *explosion11;
	CL_Surface *explosion12;
	CL_Surface *explosion13;
	CL_Surface *explosion14;
	CL_Surface *explosion15;
	CL_Surface *explosion16;
	CL_Surface *explosion17;
	CL_Surface *pause_icon;

	//CL_Sprite *spriteExplosion;

	//CL_ResourceManager *resources;

	void draw_moveable(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j);
	void draw_moveable2(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j);
	void draw_enemy(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j);
	void draw_standing(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j);
	void explode(int i, int j);
	void draw_falling(int i, int j);
	void draw_splash(int i, int j);
	//void play_sounds();

	bool first_explosion;
	bool first_splash;
};


#endif // !defined(GAMEDISPLAY_H)
