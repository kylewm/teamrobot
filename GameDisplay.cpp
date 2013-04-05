
// GameDisplay.cpp: implementation of the GameDisplay class.
//
//////////////////////////////////////////////////////////////////////

#include "GameDisplay.h"
#include "GameUI.h"
#include "TurnBot.h"
#include "WallCrawler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameDisplay::GameDisplay(GameUI *UI): cur_loc(-1.0f), ctr(0), x_start(0), y_start(0), anim_backwards(false)
{
	myUI = UI;

	// load terrain images
	floor = new CL_Surface("images/terrain/metalfloor.png");
	floorlava = new CL_Surface("images/terrain/metalfloorlava.png");
	wall = new CL_Surface("images/terrain/metal.png");
	bombable = new CL_Surface("images/terrain/bombable2.png");
	laserable = new CL_Surface("images/terrain/laserable.PNG");
	water = new CL_Surface("images/terrain/water.png");
	splash = new CL_Surface("images/terrain/splash.png");
	pit = new CL_Surface("images/terrain/lava.png");
	ns_bridge = new CL_Surface("images/terrain/ns_bridge.png");
	ew_bridge = new CL_Surface("images/terrain/ew_bridge.png");
	drillable = new CL_Surface("images/terrain/drillable.png");
	up_arrow = new CL_Surface("images/terrain/up_arrow.PNG");
	down_arrow = new CL_Surface("images/terrain/down_arrow.PNG");
	left_arrow = new CL_Surface("images/terrain/left_arrow.PNG");
	right_arrow = new CL_Surface("images/terrain/right_arrow.PNG");
	red_switch_up = new CL_Surface("images/terrain/red_switch_up.png");
	red_switch_down = new CL_Surface("images/terrain/red_switch_down.png");
	red_switch_up_h = new CL_Surface("images/terrain/red_switch_up_h.png");
	red_switch_down_h = new CL_Surface("images/terrain/red_switch_down_h.png");
	ns_red_gate = new CL_Surface("images/terrain/ns_red_gate.png");
	ew_red_gate = new CL_Surface("images/terrain/ew_red_gate.png");
	blue_switch_up = new CL_Surface("images/terrain/blue_switch_up.png");
	blue_switch_down = new CL_Surface("images/terrain/blue_switch_down.png");
	blue_switch_up_h = new CL_Surface("images/terrain/blue_switch_up_h.png");
	blue_switch_down_h = new CL_Surface("images/terrain/blue_switch_down_h.png");
	ns_blue_gate = new CL_Surface("images/terrain/ns_blue_gate.png");
	ew_blue_gate = new CL_Surface("images/terrain/ew_blue_gate.png");
	green_switch_up = new CL_Surface("images/terrain/green_switch_up.png");
	green_switch_down = new CL_Surface("images/terrain/green_switch_down.png");
	green_switch_up_h = new CL_Surface("images/terrain/green_switch_up_h.png");
	green_switch_down_h = new CL_Surface("images/terrain/green_switch_down_h.png");
	ns_green_gate = new CL_Surface("images/terrain/ns_green_gate.png");
	ew_green_gate = new CL_Surface("images/terrain/ew_green_gate.png");
	orange_switch_up = new CL_Surface("images/terrain/orange_switch_up.png");
	orange_switch_down = new CL_Surface("images/terrain/orange_switch_down.png");
	orange_switch_up_h = new CL_Surface("images/terrain/orange_switch_up_h.png");
	orange_switch_down_h = new CL_Surface("images/terrain/orange_switch_down_h.png");
	ns_orange_gate = new CL_Surface("images/terrain/ns_orange_gate.png");
	ew_orange_gate = new CL_Surface("images/terrain/ew_orange_gate.png");

	start00 = new CL_Surface("images/terrain/start00.png");
	start05 = new CL_Surface("images/terrain/start05.png");
	start10 = new CL_Surface("images/terrain/start10.png");
	start15 = new CL_Surface("images/terrain/start15.png");
	start20 = new CL_Surface("images/terrain/start20.png");
	start25 = new CL_Surface("images/terrain/start25.png");
	start30 = new CL_Surface("images/terrain/start30.png");
	start35 = new CL_Surface("images/terrain/start35.png");
	start40 = new CL_Surface("images/terrain/start40.png");
	start45 = new CL_Surface("images/terrain/start45.png");
	start50 = new CL_Surface("images/terrain/start50.png");
	start55 = new CL_Surface("images/terrain/start55.png");
	start60 = new CL_Surface("images/terrain/start60.png");
	finish00 = new CL_Surface("images/terrain/finish00.png");
	finish05 = new CL_Surface("images/terrain/finish05.png");
	finish10 = new CL_Surface("images/terrain/finish10.png");
	finish15 = new CL_Surface("images/terrain/finish15.png");
	finish20 = new CL_Surface("images/terrain/finish20.png");
	finish25 = new CL_Surface("images/terrain/finish25.png");
	finish30 = new CL_Surface("images/terrain/finish30.png");
	finish35 = new CL_Surface("images/terrain/finish35.png");
	finish40 = new CL_Surface("images/terrain/finish40.png");
	finish45 = new CL_Surface("images/terrain/finish45.png");
	finish50 = new CL_Surface("images/terrain/finish50.png");
	finish55 = new CL_Surface("images/terrain/finish55.png");
	finish60 = new CL_Surface("images/terrain/finish60.png");

	pause_icon = new CL_Surface("images/ui/paused.png");
	
	// load movable images
	selected = new CL_Surface("images/movables/selected-full-green.png");
	in_train = new CL_Surface("images/movables/highlight-full.png");
	block = new CL_Surface("images/movables/block.png");
	genericbot = new CL_Surface("images/movables/genericbot.png");
	caboosebot = new CL_Surface("images/movables/caboosebot.png");
	bridgebot = new CL_Surface("images/movables/bridgebot.png");
	arrowbot = new CL_Surface("images/movables/arrowbot.png");
	drillbot = new CL_Surface("images/movables/drillbot.png");
	pushbot = new CL_Surface("images/movables/pushbot.png");
	decoybot = new CL_Surface("images/movables/baitbot.png");
	bombbot = new CL_Surface("images/movables/bombbot.png");
	turnbot_left = new CL_Surface("images/movables/turnbot_left.png");
	turnbot_right = new CL_Surface("images/movables/turnbot_right.png");
	wallcrawler_left = new CL_Surface("images/movables/wallcrawler_left.png");
	wallcrawler_right = new CL_Surface("images/movables/wallcrawler_right.png");
	swimbot = new CL_Surface("images/movables/swimbot.png");
	swimbotUnderwater = new CL_Surface("images/movables/swimbot_under.png");
	enemy = new CL_Surface("images/movables/enemybot.png");

	explosion1 = new CL_Surface("images/terrain/explosion_01.png");
	explosion2 = new CL_Surface("images/terrain/explosion_02.png");
	explosion3 = new CL_Surface("images/terrain/explosion_03.png");
	explosion4 = new CL_Surface("images/terrain/explosion_04.png");
	explosion5 = new CL_Surface("images/terrain/explosion_05.png");
	explosion6 = new CL_Surface("images/terrain/explosion_06.png");
	explosion7 = new CL_Surface("images/terrain/explosion_07.png");
	explosion8 = new CL_Surface("images/terrain/explosion_08.png");
	explosion9 = new CL_Surface("images/terrain/explosion_09.png");
	explosion10 = new CL_Surface("images/terrain/explosion_10.png");
	explosion11 = new CL_Surface("images/terrain/explosion_11.png");
	explosion12 = new CL_Surface("images/terrain/explosion_12.png");
	explosion13 = new CL_Surface("images/terrain/explosion_13.png");
	explosion14 = new CL_Surface("images/terrain/explosion_14.png");
	explosion15 = new CL_Surface("images/terrain/explosion_15.png");
	explosion16 = new CL_Surface("images/terrain/explosion_16.png");
	explosion17 = new CL_Surface("images/terrain/explosion_17.png");

	time1 = 250;
	time2 = 500;
	time3 = 750;
	time4 = 1000;

	time_ctr = time4 / 13;

	myBoard = NULL;

	// load board images
	try {
		//resources = new CL_ResourceManager("resources.xml");
		//spriteExplosion = new CL_Sprite("spriteExplosion", resources);
	}
	catch (CL_Error e)
	{
		std::cout << e.message.c_str() << std::endl;
		
		// Display console close message and wait for a key
		//console.display_close_message();
	}

}


GameDisplay::~GameDisplay()
{
	// delete terrain surfaces
	delete floor;
	delete floorlava;
	delete wall;
	delete bombable;
	delete laserable;
	delete water;
	delete pit;
	delete ns_bridge;
	delete ew_bridge;
	delete drillable;
	delete up_arrow;
	delete down_arrow;
	delete left_arrow;
	delete right_arrow;
	delete red_switch_up;
	delete red_switch_down;
	delete red_switch_up_h;
	delete red_switch_down_h;
	delete ns_red_gate;
	delete ew_red_gate;
	delete blue_switch_up;
	delete blue_switch_down;
	delete blue_switch_up_h;
	delete blue_switch_down_h;
	delete ns_blue_gate;
	delete ew_blue_gate;
	delete green_switch_up;
	delete green_switch_down;
	delete green_switch_up_h;
	delete green_switch_down_h;
	delete ns_green_gate;
	delete ew_green_gate;
	delete orange_switch_up;
	delete orange_switch_down;
	delete orange_switch_up_h;
	delete orange_switch_down_h;
	delete ns_orange_gate;
	delete ew_orange_gate;
	delete start00;
	delete start05;
	delete start10;
	delete start15;
	delete start20;
	delete start25;
	delete start30;
	delete start35;
	delete start40;
	delete start45;
	delete start50;
	delete start55;
	delete start60;
	delete finish00;
	delete finish05;
	delete finish10;
	delete finish15;
	delete finish20;
	delete finish25;
	delete finish30;
	delete finish35;
	delete finish40;
	delete finish45;
	delete finish50;
	delete finish55;
	delete finish60;
	delete pause_icon;
	delete selected;
	delete in_train;
	
	// delete movable surfaces
	delete block;
	delete genericbot;
	delete caboosebot;
	delete bridgebot;
	delete arrowbot;
	delete drillbot;
	delete pushbot;
	delete decoybot;
	delete bombbot;
	delete turnbot_left;
	delete turnbot_right;
	delete wallcrawler_left;
	delete wallcrawler_right;
	delete swimbot;
	delete swimbotUnderwater;
	delete enemy;
	delete explosion1;
	delete explosion2;
	delete explosion3;
	delete explosion4;
	delete explosion5;
	delete explosion6;
	delete explosion7;
	delete explosion8;
	delete explosion9;
	delete explosion10;
	delete explosion11;
	delete explosion12;
	delete explosion13;
	delete explosion14;
	delete explosion15;
	delete explosion16;
	delete explosion17;

	// delete sprites
	//delete spriteExplosion;

	//delete random stuff
	//delete resources;
	delete myBoard;
	
}


void GameDisplay::initLevel(int curLevel)
{
	if(myBoard != NULL) {
		delete myBoard;
	}

	myUI->first_arrow_clicked = false;

	myBoard = new GameBoard();
	switch (curLevel) {
	case 1:
		myBoard->loadBoard("levels/level01.txt");
		break;
	case 2:
		myBoard->loadBoard("levels/level02.txt");
		break;
	case 3:
		myBoard->loadBoard("levels/level03.txt");
		break;
	case 4:
		myBoard->loadBoard("levels/level04.txt");
		break;
	case 5:
		myBoard->loadBoard("levels/level05.txt");
		break;
	case 6:
		myBoard->loadBoard("levels/level06.txt");
		break;
	case 7:
		myBoard->loadBoard("levels/level07.txt");
		break;
	case 8:
		myBoard->loadBoard("levels/level08.txt");
		break;
	case 9:
		myBoard->loadBoard("levels/level09.txt");
		break;
	case 10:
		myBoard->loadBoard("levels/level10.txt");
		break;
	case 11:
		myBoard->loadBoard("levels/level11.txt");
		break;
	case 12:
		myBoard->loadBoard("levels/level12.txt");
		break;
	case 13:
		myBoard->loadBoard("levels/level13.txt");
		break;
	case 14:
		myBoard->loadBoard("levels/level14.txt");
		break;
	case 15:
		myBoard->loadBoard("levels/level15.txt");
		break;
	case 16:
		myBoard->loadBoard("levels/level16.txt");
		break;
	case 17:
		myBoard->loadBoard("levels/level17.txt");
		break;
	case 18:
		myBoard->loadBoard("levels/level18.txt");
		break;
	case 19:
		myBoard->loadBoard("levels/level19.txt");
		break;
	case 20:
		myBoard->loadBoard("levels/level20.txt");
		break;
	case 21:
		myBoard->loadBoard("levels/level21.txt");
		break;
	case 22:
		myBoard->loadBoard("levels/level22.txt");
		break;
	case 23:
		myBoard->loadBoard("levels/level23.txt");
		break;
	case 24:
		myBoard->loadBoard("levels/level24.txt");
		break;
	case 25:
		myBoard->loadBoard("levels/level25.txt");
		break;
	case 26:
		myBoard->loadBoard("levels/level26.txt");
		break;
	case 27:
		myBoard->loadBoard("levels/level27.txt");
		break;
	case 28:
		myBoard->loadBoard("levels/level28.txt");
		break;
	case 29:
		myBoard->loadBoard("levels/level29.txt");
		break;
	case 30:
		myBoard->loadBoard("levels/level30.txt");
		break;
	case 31:
		myUI->showCredits();
		// no break here, fall through to replay level 1

	default:
		myBoard->loadBoard("levels/level01.txt");
		myUI->setCurLevel(1);
	}
	
}


gameState_t GameDisplay::show(bool paused)
{
	if (ctr == -1) {
		begin_time = CL_System::get_time();
	}
	ctr = CL_System::get_time() - begin_time;
	cur_loc = -1.0f + ((float) ctr / (float) time4);
	
	//pit->draw(x_start, y_start);
	//water->draw(x_start, y_start + 300);

	GameTile *curTile;

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			curTile = myBoard->getTileAt(j,i);
			
			// draw secondary terrain
			
			switch (curTile->getSecondaryTerrain()) {
			case FLOOR:
				floor->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case FLOOR_LAVA:
				floorlava->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case WALL:
				wall->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case BOMBABLE:
				bombable->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case LASERABLE:
				laserable->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case DRILLABLE:
				drillable->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case WATER:

				water->draw(CL_Rect(i * 30 + x_start + 1, j * 30 + y_start, i * 30 + x_start + 30 + 1, j * 30 + y_start + 30), 
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
				
				break;
			case PIT:
				pit->draw(CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30), 
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
				break;		
			case NS_BRIDGE:
				ns_bridge->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_BRIDGE:
				ew_bridge->draw(i * 30 + x_start, j * 30 + y_start);
				break;	
			case HEAVYREDSWITCH_UP:
				red_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYGREENSWITCH_UP:
				green_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYBLUESWITCH_UP:
				blue_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYORANGESWITCH_UP:
				orange_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case REDSWITCH_UP:
				red_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case GREENSWITCH_UP:
				green_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case BLUESWITCH_UP:
				blue_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case ORANGESWITCH_UP:
				orange_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYREDSWITCH_DOWN:
				red_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYGREENSWITCH_DOWN:
				green_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYBLUESWITCH_DOWN:
				blue_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYORANGESWITCH_DOWN:
				orange_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case REDSWITCH_DOWN:
				red_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case GREENSWITCH_DOWN:
				green_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case BLUESWITCH_DOWN:
				blue_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case ORANGESWITCH_DOWN:
				orange_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_REDGATE:
				ns_red_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_REDGATE:
				ew_red_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_GREENGATE:
				ns_green_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_GREENGATE:
				ew_green_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_BLUEGATE:
				ns_blue_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_BLUEGATE:
				ew_blue_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_ORANGEGATE:
				ns_orange_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_ORANGEGATE:
				ew_orange_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case UPARROW:
				up_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case DOWNARROW:
				down_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case LEFTARROW:
				left_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case RIGHTARROW:
				right_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_UPARROW:
				up_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_DOWNARROW:
				down_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_LEFTARROW:
				left_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_RIGHTARROW:
				right_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case START:
				start00->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case FINISH:
				finish00->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			default:
				printf("GameDisplay.cpp Error - Invalid secondary terrain at x = %i, y = %i\n", i, j);
			}
			
			// draw primary terrain
			
			switch (curTile->getPrimaryTerrain()) {
			case FLOOR:
				floor->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case FLOOR_LAVA:
				floorlava->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case WALL:
				wall->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case BOMBABLE:
				bombable->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case LASERABLE:
				laserable->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case DRILLABLE:
				drillable->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case WATER:
	
				water->draw(CL_Rect(i * 30 + x_start + 1, j * 30 + y_start, i * 30 + x_start + 30 + 1, j * 30 + y_start + 30), 
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
				
				break;
			case PIT:
				pit->draw(CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30), 
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
				break;
			case NS_BRIDGE:
				ns_bridge->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_BRIDGE:
				ew_bridge->draw(i * 30 + x_start, j * 30 + y_start);
				break;	
			case HEAVYREDSWITCH_UP:
				red_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYGREENSWITCH_UP:
				green_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYBLUESWITCH_UP:
				blue_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYORANGESWITCH_UP:
				orange_switch_up_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case REDSWITCH_UP:
				red_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case GREENSWITCH_UP:
				green_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case BLUESWITCH_UP:
				blue_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case ORANGESWITCH_UP:
				orange_switch_up->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYREDSWITCH_DOWN:
				red_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYGREENSWITCH_DOWN:
				green_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYBLUESWITCH_DOWN:
				blue_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case HEAVYORANGESWITCH_DOWN:
				orange_switch_down_h->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case REDSWITCH_DOWN:
				red_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case GREENSWITCH_DOWN:
				green_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case BLUESWITCH_DOWN:
				blue_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case ORANGESWITCH_DOWN:
				orange_switch_down->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_REDGATE:
				ns_red_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_REDGATE:
				ew_red_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_GREENGATE:
				ns_green_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_GREENGATE:
				ew_green_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_BLUEGATE:
				ns_blue_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_BLUEGATE:
				ew_blue_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case NS_ORANGEGATE:
				ns_orange_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case EW_ORANGEGATE:
				ew_orange_gate->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case UPARROW:
				up_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case DOWNARROW:
				down_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case LEFTARROW:
				left_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case RIGHTARROW:
				right_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_UPARROW:
				up_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_DOWNARROW:
				down_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_LEFTARROW:
				left_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case R_RIGHTARROW:
				right_arrow->draw(i * 30 + x_start, j * 30 + y_start);
				break;
			case START:
				if (!anim_backwards) {
					if (ctr < time_ctr) {
						start00->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 2 * time_ctr) {
						start05->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 3 * time_ctr) {
						start10->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 4 * time_ctr) {
						start15->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 5 * time_ctr) {
						start20->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 6 * time_ctr) {
						start25->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 7 * time_ctr) {
						start30->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 8 * time_ctr) {
						start35->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 9 * time_ctr) {
						start40->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 10 * time_ctr) {
						start45->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 11 * time_ctr) {
						start50->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 12 * time_ctr) {
						start55->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else {
						start60->draw(i * 30 + x_start, j * 30 + y_start);
					}
				}
				else {
					if (ctr < time_ctr) {
						start60->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 2 * time_ctr) {
						start55->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 3 * time_ctr) {
						start50->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 4 * time_ctr) {
						start45->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 5 * time_ctr) {
						start40->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 6 * time_ctr) {
						start35->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 7 * time_ctr) {
						start30->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 8 * time_ctr) {
						start25->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 9 * time_ctr) {
						start20->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 10 * time_ctr) {
						start15->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 11 * time_ctr) {
						start10->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 12 * time_ctr) {
						start05->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else {
						start00->draw(i * 30 + x_start, j * 30 + y_start);
					}
				}

				break;
			case FINISH:
				if (!anim_backwards) {
					if (ctr < time_ctr) {
						finish00->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 2 * time_ctr) {
						finish05->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 3 * time_ctr) {
						finish10->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 4 * time_ctr) {
						finish15->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 5 * time_ctr) {
						finish20->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 6 * time_ctr) {
						finish25->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 7 * time_ctr) {
						finish30->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 8 * time_ctr) {
						finish35->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 9 * time_ctr) {
						finish40->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 10 * time_ctr) {
						finish45->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 11 * time_ctr) {
						finish50->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 12 * time_ctr) {
						finish55->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else {
						finish60->draw(i * 30 + x_start, j * 30 + y_start);
					}
				}
				else {
					if (ctr < time_ctr) {
						finish60->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 2 * time_ctr) {
						finish55->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 3 * time_ctr) {
						finish50->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 4 * time_ctr) {
						finish45->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 5 * time_ctr) {
						finish40->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 6 * time_ctr) {
						finish35->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 7 * time_ctr) {
						finish30->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 8 * time_ctr) {
						finish25->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 9 * time_ctr) {
						finish20->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 10 * time_ctr) {
						finish15->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 11 * time_ctr) {
						finish10->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else if (ctr < 12 * time_ctr) {
						finish05->draw(i * 30 + x_start, j * 30 + y_start);
					}
					else {
						finish00->draw(i * 30 + x_start, j * 30 + y_start);
					}
				}

				break;
			default:
				printf("GameDisplay.cpp Error - Invalid primary terrain at x = %i, y = %i\n", i, j);
			}

			//Draw any exploding terrain
			if(curTile->getTerrainExploding()) {
				if (ctr < time2) {
					explode(i * 30 + x_start, j * 30 + y_start);
				}
			}
		}
	}
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			curTile = myBoard->getTileAt(j,i);
			
			// draw highlights under train
			
			vector<Moveable*> moveableList = curTile->getMoveableList();
			vector<Moveable*>::iterator iter = moveableList.begin();
			for (iter; iter != moveableList.end(); ++iter) {
				
				Moveable *curMoveable = *iter;
				if (curMoveable->getX() == curMoveable->getPrevX() && curMoveable->getY() == curMoveable->getPrevY()) {
					if (!(curMoveable->getExploding() || curMoveable->getFalling() || curMoveable->getDrowning())) {
						switch (curMoveable->getPrevDirection()) 
						{
						case DOWN:
							
							if (curMoveable->getInTrain()) {
								in_train->draw(i * 30 + x_start, j * 30 + y_start);
							}
							if (curMoveable->getSelected()) {
								selected->draw(i * 30 + x_start, j * 30 + y_start);
							}
							break;
						case UP:
							
							if (curMoveable->getInTrain()) {
								in_train->draw(i * 30 + x_start, j * 30 + y_start);
							}
							if (curMoveable->getSelected()) {
								selected->draw(i * 30 + x_start, j * 30 + y_start);
							}
							break;
						case LEFT:
							
							if (curMoveable->getInTrain()) {
								in_train->draw(i * 30 + x_start, j * 30 + y_start);
							}
							if (curMoveable->getSelected()) {
								selected->draw(i * 30 + x_start, j * 30 + y_start);
							}
							break;
						case RIGHT:
							
							if (curMoveable->getInTrain()) {
								in_train->draw(i * 30 + x_start, j * 30 + y_start);
							}
							if (curMoveable->getSelected()) {
								selected->draw(i * 30 + x_start, j * 30 + y_start);
							}
							break;
						default:
							break;
						} // end switch
					}
				}
					else {
						if (!(curMoveable->getExploding() || curMoveable->getFalling() || curMoveable->getDrowning())) {
							switch (curMoveable->getPrevDirection()) 
							{
							case DOWN:
								
								if (curMoveable->getInTrain()) {
									in_train->draw(i * 30 + x_start, (j+cur_loc) * 30 + y_start);
								}
								if (curMoveable->getSelected()) {
									selected->draw(i * 30 + x_start, (j+cur_loc) * 30 + y_start);
								}
								break;
							case UP:
								
								if (curMoveable->getInTrain()) {
									in_train->draw(i * 30 + x_start, (j-cur_loc) * 30 + y_start);
								}
								if (curMoveable->getSelected()) {
									selected->draw(i * 30 + x_start, (j-cur_loc) * 30 + y_start);
								}
								break;
							case LEFT:
								
								if (curMoveable->getInTrain()) {
									in_train->draw((i-cur_loc) * 30 + x_start, j * 30 + y_start);
								}
								if (curMoveable->getSelected()) {
									selected->draw((i-cur_loc) * 30 + x_start, j * 30 + y_start);
								}
								break;
							case RIGHT:
								
								if (curMoveable->getInTrain()) {
									in_train->draw((i+cur_loc) * 30 + x_start, j * 30 + y_start);
								}
								if (curMoveable->getSelected()) {
									selected->draw((i+cur_loc) * 30 + x_start, j * 30 + y_start);
								}
								break;
							default:
								break;
							} // end switch
						} // end if (!(curMoveable...
					} // end else
				} // end for (iter...
			} // end for (int i = 0...
	} // end for (j = 0...
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			curTile = myBoard->getTileAt(j,i);
			
			// draw moveables
			
			vector<Moveable*> moveableList = curTile->getMoveableList();
			vector<Moveable*>::iterator iter = moveableList.begin();
			for (iter; iter != moveableList.end(); ++iter) {
				
				Moveable *curMoveable = *iter;
				
				switch (curMoveable->getType()) 
				{
					
				case GENERICBOT:

					draw_moveable(genericbot, curMoveable, i, j);
					
					break;
						
				case DRILLBOT:

					draw_moveable2(drillbot, curMoveable, i, j);

					break;
							
				case PUSHBOT:

					draw_moveable(pushbot, curMoveable, i, j);

					break;

				case BOMBBOT:

					draw_moveable(bombbot, curMoveable, i, j);

					break;

				case TURNBOT:

					if (curMoveable->getInTrain()) {
						if (myUI->getOptionsCode() == TURNLEFT) {
							draw_moveable(turnbot_left, curMoveable, i, j);
						}
						else { // TURNRIGHT
							draw_moveable(turnbot_right, curMoveable, i, j);
						}
					}
					else {
						if (((TurnBot *) curMoveable)->getTurnDirection() == TURNLEFT) {
							draw_moveable(turnbot_left, curMoveable, i, j);
						}
						else { // TURNRIGHT
							draw_moveable(turnbot_right, curMoveable, i, j);
						}
					}
					//draw_moveable(turnbot_left, curMoveable, i, j);

					break;

				case WALLCRAWLER:

					if (curMoveable->getInTrain()) {
						if (myUI->getOptionsCode() == LEFTSIDE) {
							draw_moveable(wallcrawler_left, curMoveable, i, j);
						}
						else { // RIGHTSIDE
							draw_moveable(wallcrawler_right, curMoveable, i, j);
						}
					}
					else {
						if (((WallCrawler *) curMoveable)->getCrawlDirection() == LEFTSIDE) {
							draw_moveable(wallcrawler_left, curMoveable, i, j);
						}
						else { // RIGHTSIDE
							draw_moveable(wallcrawler_right, curMoveable, i, j);
						}
					}
					//draw_moveable(wallcrawler_left, curMoveable, i, j);

					break;

				case SWIMBOT:

					if ((myBoard->getTileAt(curMoveable->getPrevY(),curMoveable->getPrevX()))->getPrimaryTerrain() != WATER) {
						if (curTile->getPrimaryTerrain() == WATER && ctr > time2) {
							draw_moveable(swimbotUnderwater, curMoveable, i, j);
						}
						else {
							draw_moveable(swimbot, curMoveable, i, j);
						}
					}
					else {
						if (curTile->getPrimaryTerrain() != WATER && ctr > time2) {
							draw_moveable(swimbot, curMoveable, i, j);
						}
						else {
							draw_moveable(swimbotUnderwater, curMoveable, i, j);
						}
					}

					break;

				case REDIRECTBOT:

					draw_moveable(arrowbot, curMoveable, i, j);

					break;

				case BRIDGEBOT:

					draw_moveable(bridgebot, curMoveable, i, j);

					break;

				case CABOOSEBOT:

					draw_moveable2(caboosebot, curMoveable, i, j);

					break;

				case ENEMY:

					draw_enemy(enemy, curMoveable, i, j);

					break;

				case DECOYBOT:

					draw_moveable(decoybot, curMoveable, i, j);

					break;

				case BLOCK:
						draw_moveable(block, curMoveable, i, j);

					break;

				default:
					break;
				}

			}
			//}
		}
	}
	
	if (!paused) {
		//ctr++;
		//cur_loc += .0208f;
		if (ctr >= time4) {
			myBoard->nextTurn();
			//play_sounds();
			first_explosion = true;
			first_splash = true;
			//ctr = -1;
			myUI->first_frame();
			begin_time = CL_System::get_time();
			anim_backwards = !anim_backwards;
			//cur_loc = -1.0f;
		}
	}
	else {
		pause_icon->draw(141,250);
	}
	
	return myBoard->getGameState();
	
}


void GameDisplay::draw_moveable(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j) {
	if (curMoveable->getX() == curMoveable->getPrevX() && curMoveable->getY() == curMoveable->getPrevY()) {
		draw_standing(moveable_surf, curMoveable, i, j);
	}
	else {
	switch (curMoveable->getPrevDirection()) 
	{
	case DOWN:
		if (curMoveable->getExploding()) {
			explode(i * 30 + x_start, (j - curMoveable->getExplodingDistance()) * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2 && curMoveable->getType() != BLOCK) {
				draw_splash(i, j);
		}
		else if (ctr < time1) {
			//if (curMoveable->getInTrain()) {
			//genericbot->draw(CL_Rect(0,0,30,30),
			//	CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
			//}
			//else {
			moveable_surf->draw(CL_Rect(0,0,30,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
			//}
		}
		else if (ctr < time2) {
			//if (curMoveable->getInTrain()) {
			//genericbot->draw(CL_Rect(30,0,60,30),
			//	CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
			//}
			//else {
			moveable_surf->draw(CL_Rect(30,0,60,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
			//}
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,0,90,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,0,60,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		break;
	case UP:
		if (curMoveable->getExploding()) {
			explode(i * 30 + x_start, (j + curMoveable->getExplodingDistance()) * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,30,30,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
			//}
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,30,60,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,30,90,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,30,60,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		break;
	case LEFT:
		if (curMoveable->getExploding()) {
			explode((i + curMoveable->getExplodingDistance()) * 30 + x_start, j * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,60,30,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,60,60,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,60,90,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,60,60,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		break;
	case RIGHT:
		if (curMoveable->getExploding()) {
			explode((i - curMoveable->getExplodingDistance()) * 30 + x_start, j * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2 && curMoveable->getType() != BLOCK) {
			draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,90,30,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,90,60,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,90,90,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,90,60,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		break;
	default:
		break;
		
	}
	}
} // end drawMoveable

void GameDisplay::draw_moveable2(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j) {
	if (curMoveable->getX() == curMoveable->getPrevX() && curMoveable->getY() == curMoveable->getPrevY()) {
		draw_standing(moveable_surf, curMoveable, i, j);
	}
	else {

	switch (curMoveable->getPrevDirection()) 
	{
	case DOWN:
		if (curMoveable->getExploding()) {
			explode(i * 30 + x_start, (j - curMoveable->getExplodingDistance()) * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
				draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
				draw_splash(i, j);
		}
		else if (ctr < time4 / 6) {
			moveable_surf->draw(CL_Rect(0,0,30,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 2 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,0,60,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 3 * time4 / 6) {
			moveable_surf->draw(CL_Rect(60,0,90,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 4 * time4 / 6) {
			moveable_surf->draw(CL_Rect(0,0,30,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 5 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,0,60,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(60,0,90,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		break;
	case UP:
		if (curMoveable->getExploding()) {
			explode(i * 30 + x_start, (j + curMoveable->getExplodingDistance()) * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
			draw_splash(i, j);
		}
		else if (ctr < time4 / 6) {
			moveable_surf->draw(CL_Rect(0,30,30,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 2 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,30,60,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 3 * time4 / 6) {
			moveable_surf->draw(CL_Rect(60,30,90,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 4 * time4 / 6) {
			moveable_surf->draw(CL_Rect(0,30,30,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else if (ctr < 5 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,30,60,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(60,30,90,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		break;
	case LEFT:
		if (curMoveable->getExploding()) {
			explode((i + curMoveable->getExplodingDistance()) * 30 + x_start, j * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
			draw_splash(i, j);
		}
		else if (ctr < time4 / 6) {
			moveable_surf->draw(CL_Rect(0,60,30,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 2 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,60,60,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 3 * time4 / 6) {
			moveable_surf->draw(CL_Rect(60,60,90,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 4 * time4 / 6) {
			moveable_surf->draw(CL_Rect(0,60,30,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 5 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,60,60,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(60,60,90,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		break;
	case RIGHT:
		if (curMoveable->getExploding()) {
			explode((i - curMoveable->getExplodingDistance()) * 30 + x_start, j * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
			draw_splash(i, j);
		}
		else if (ctr < time4 / 6) {
			moveable_surf->draw(CL_Rect(0,90,30,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 2 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,90,60,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 3 * time4 / 6) {
			moveable_surf->draw(CL_Rect(60,90,90,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 4 * time4 / 6) {
			moveable_surf->draw(CL_Rect(0,90,30,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else if (ctr < 5 * time4 / 6) {
			moveable_surf->draw(CL_Rect(30,90,60,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(60,90,90,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		break;
	default:
		break;
		
	}
	}
} // end drawMoveable2



void GameDisplay::draw_enemy(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j) {
	int dir;
	if (curMoveable->getX() == curMoveable->getPrevX() && curMoveable->getY() == curMoveable->getPrevY()
		&& !curMoveable->getUTurn()) {
		draw_standing(moveable_surf, curMoveable, i, j);
	}
	else {

	if (!curMoveable->getUTurn() || ctr < time2) { 
		dir = curMoveable->getPrevDirection();
	}
	else { // enemy making a uTurn, draw half prev direction, half current direction
		dir = curMoveable->getDirection();
	}

	int adj = 0;
	if(curMoveable->getUTurn()) {
		adj = 30;
	}

	switch (dir) 
	{
	case DOWN:
		if (curMoveable->getExploding()) {
			explode(i * 30 + x_start, (j - curMoveable->getExplodingDistance()) * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
				draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
				draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,0,30,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start + adj, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30 + adj));
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,0,60,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start + adj, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30 + adj));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,0,90,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,0,60,30),
				CL_Rect(i * 30 + x_start, (j+cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j+cur_loc) * 30 + y_start + 30));
		}
		break;
	case UP:
		if (curMoveable->getExploding()) {
			explode(i * 30 + x_start, (j + curMoveable->getExplodingDistance()) * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
			draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,30,30,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start - adj, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30 - adj));
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,30,60,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start - adj, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30 - adj));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,30,90,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,30,60,60),
				CL_Rect(i * 30 + x_start, (j-cur_loc) * 30 + y_start, i * 30 + x_start + 30, (j-cur_loc) * 30 + y_start + 30));
		}
		break;
	case LEFT:
		if (curMoveable->getExploding()) {
			explode((i + curMoveable->getExplodingDistance()) * 30 + x_start, j * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
			draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,60,30,90),
				CL_Rect((i-cur_loc) * 30 + x_start - adj, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30 - adj, j * 30 + y_start + 30));
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,60,60,90),
				CL_Rect((i-cur_loc) * 30 + x_start - adj, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30 - adj, j * 30 + y_start + 30));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,60,90,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,60,60,90),
				CL_Rect((i-cur_loc) * 30 + x_start, j * 30 + y_start, (i-cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		break;
	case RIGHT:
		if (curMoveable->getExploding()) {
			explode((i - curMoveable->getExplodingDistance()) * 30 + x_start, j * 30 + y_start);
		}
		else if (curMoveable->getFalling() && ctr > time2) {
			draw_falling(i, j);
		}
		else if (curMoveable->getDrowning() && ctr > time2) {
			draw_splash(i, j);
		}
		else if (ctr < time1) {
			moveable_surf->draw(CL_Rect(0,90,30,120),
				CL_Rect((i+cur_loc) * 30 + x_start + adj, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30 + adj, j * 30 + y_start + 30));
		}
		else if (ctr < time2) {
			moveable_surf->draw(CL_Rect(30,90,60,120),
				CL_Rect((i+cur_loc) * 30 + x_start + adj, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30 + adj, j * 30 + y_start + 30));
		}
		else if (ctr < time3) {
			moveable_surf->draw(CL_Rect(60,90,90,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		else {
			moveable_surf->draw(CL_Rect(30,90,60,120),
				CL_Rect((i+cur_loc) * 30 + x_start, j * 30 + y_start, (i+cur_loc) * 30 + x_start + 30, j * 30 + y_start + 30));
		}
		break;
	default:
		break;
		
	}
	}

} // end drawEnemy



void GameDisplay::draw_standing(CL_Surface *moveable_surf, Moveable *curMoveable, int i, int j) {
	
	if (curMoveable->getExploding()) {
		explode(i * 30 + x_start, j * 30 + y_start);
	}
	else if (curMoveable->getFalling() && ctr > time2 && curMoveable->getType() != BLOCK) {
		draw_falling(i, j);
	}
	else if (curMoveable->getDrowning() && ctr > time2 && curMoveable->getType() != BLOCK) {
		draw_splash(i, j);
	}
	else {
		switch (curMoveable->getPrevDirection()) 
		{
		case DOWN:
			if (ctr < time1) {
				moveable_surf->draw(CL_Rect(0,0,30,30),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time2) {
				moveable_surf->draw(CL_Rect(30,0,60,30),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time3) {
				moveable_surf->draw(CL_Rect(60,0,90,30),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else {
				moveable_surf->draw(CL_Rect(30,0,60,30),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			break;
		case UP:
			if (ctr < time1) {
				moveable_surf->draw(CL_Rect(0,30,30,60),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time2) {
				moveable_surf->draw(CL_Rect(30,30,60,60),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time3) {
				moveable_surf->draw(CL_Rect(60,30,90,60),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else {
				moveable_surf->draw(CL_Rect(30,30,60,60),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			break;
		case LEFT:
			if (ctr < time1) {
				moveable_surf->draw(CL_Rect(0,60,30,90),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time2) {
				moveable_surf->draw(CL_Rect(30,60,60,90),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time3) {
				moveable_surf->draw(CL_Rect(60,60,90,90),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else {
				moveable_surf->draw(CL_Rect(30,60,60,90),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			break;
		case RIGHT:
			if (ctr < time1) {
				moveable_surf->draw(CL_Rect(0,90,30,120),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time2) {
				moveable_surf->draw(CL_Rect(30,90,60,120),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else if (ctr < time3) {
				moveable_surf->draw(CL_Rect(60,90,90,120),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			else {
				moveable_surf->draw(CL_Rect(30,90,60,120),
					CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
			}
			break;
		default:
			break;
			
	}
		}
} // end draw_standing



void GameDisplay::explode(int i, int j)
{
	if (ctr < time2 / 17) {
		//printf("should drawing exploding");
		if (first_explosion) {
			myUI->snd_player.playSound(EXPLOSION);
			first_explosion = false;
		}
		explosion1->draw(i, j);
	}
	else if (ctr < 2 * time2 / 17){
		explosion2->draw(i, j);
	}
	else if (ctr < 3 * time2 / 17){
		explosion3->draw(i, j);
	}
	else if (ctr < 4 * time2 / 17){
		explosion4->draw(i, j);
	}
	else if (ctr < 5 * time2 / 17){
		explosion5->draw(i, j);
	}
	else if (ctr < 6 * time2 / 17){
		explosion6->draw(i, j);
	}
	else if (ctr < 7 * time2 / 17){
		explosion7->draw(i, j);
	}
	else if (ctr < 8 * time2 / 17){
		explosion8->draw(i, j);
	}
	else if (ctr < 9 * time2 / 17){
		explosion9->draw(i, j);
	}
	else if (ctr < 10 * time2 / 17){
		explosion10->draw(i, j);
	}
	else if (ctr < 11 * time2 / 17){
		explosion11->draw(i, j);
	}
	else if (ctr < 12 * time2 / 17){
		explosion12->draw(i, j);
	}
	else if (ctr < 13 * time2 / 17){
		explosion13->draw(i, j);
	}
	else if (ctr < 14 * time2 / 17){
		explosion14->draw(i, j);
	}
	else if (ctr < 15 * time2 / 17){
		explosion15->draw(i, j);
	}
	else if (ctr < 16 * time2 / 17){
		explosion16->draw(i, j);
	}
	else {
		explosion17->draw(i, j);
	}
}

void GameDisplay::draw_falling(int i, int j)
{
	if (ctr < time2 / 17) {
		if (first_explosion) {
			myUI->snd_player.playSound(EXPLOSION);
			first_explosion = false;
		}
		explosion1->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 2 * (time4-time2) / 17 + time2){
		if (first_explosion) {
			myUI->snd_player.playSound(EXPLOSION);
			first_explosion = false;
		}
		explosion2->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 3 * (time4-time2) / 17 + time2){
		explosion3->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 4 * (time4-time2) / 17 + time2){
		explosion4->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 5 * (time4-time2) / 17 + time2){
		explosion5->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 6 * (time4-time2) / 17 + time2){
		explosion6->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 7 * (time4-time2) / 17 + time2){
		explosion7->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 8 * (time4-time2) / 17 + time2){
		explosion8->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 9 * (time4-time2) / 17 + time2){
		explosion9->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 10 * (time4-time2) / 17 + time2){
		explosion10->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 11 * (time4-time2) / 17 + time2){
		explosion11->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 12 * (time4-time2) / 17 + time2){
		explosion12->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 13 * (time4-time2) / 17 + time2){
		explosion13->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 14 * (time4-time2) / 17 + time2){
		explosion14->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 15 * (time4-time2) / 17 + time2){
		explosion15->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else if (ctr < 16 * (time4-time2) / 17 + time2){
		explosion16->draw(i * 30 + x_start, j * 30 + y_start);
	}
	else {
		explosion17->draw(i * 30 + x_start, j * 30 + y_start);
	}
}

void GameDisplay::draw_splash(int i, int j) {
	if (ctr < (time4-time2) / 12 + time2) {
		if (first_splash) {
			myUI->snd_player.playSound(SPLASH);
			first_splash = false;
		}
		splash->draw(CL_Rect(0,0,30,30),
			CL_Rect(i * 30 + x_start, j * 30 + y_start , i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 2 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(30,0,60,30), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 3 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(60,0,90,30), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 4 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(0,30,30,60), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 5 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(30,30,60,60), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 6 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(60,30,90,60), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 7 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(0,60,30,90), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 8 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(30,60,60,90), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 9 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(60,60,90,90), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 10 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(0,90,30,120), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else if (ctr < 11 * (time4-time2) / 12 + time2){
		splash->draw(CL_Rect(30,90,60,120), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
	else /*if (ctr < 12 * (time4-time2) / 12 + time2)*/{
		splash->draw(CL_Rect(60,90,90,120), 
			CL_Rect(i * 30 + x_start, j * 30 + y_start, i * 30 + x_start + 30, j * 30 + y_start + 30));
	}
}

/* called right after next_turn to check for explosions, splashes, that sort of thing
void GameDisplay::play_sounds() {
	GameTile *curTile;
	bool explosion = false;
	bool splash = false;

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			curTile = myBoard->getTileAt(j,i);
			vector<Moveable*> moveableList = curTile->getMoveableList();
			vector<Moveable*>::iterator iter = moveableList.begin();
			for (iter; iter != moveableList.end(); ++iter) {
				Moveable *curMoveable = *iter;
				if (curMoveable->getExploding()) explosion = true;
				else if (curMoveable->getDrowning()) splash = true;
			}
		}
	}	
	if (explosion)	myUI->snd_player.playSound(EXPLOSION);
	if (splash)		myUI->snd_player.playSound(SPLASH);
}*/
