// GameUI.h: interface for the GameUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(GAMEUI_H)
#define GAMEUI_H

#include <ClanLib/core.h>
#include <ClanLib/guistylesilver.h>
#include <ClanLib/gui.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include "GameDisplay.h"
#include "team_robot.h"
#include "Sound.h"

// this represents a clickable object
typedef struct box {
	int x;
	int y;
	int width;
	int height;
} box_t;

class GameUI  
{
public:
	Sound snd_player;
	bool first_arrow_clicked;

	GameUI();
	virtual ~GameUI();
	void on_quit();
	void on_button_press(const CL_InputEvent &);
	void on_button_down(const CL_InputEvent &);
	void on_key_press(const CL_InputEvent &);
	void on_close_2(/*CL_SlotParent_v0 &*/);
	void restart();
	void next_level(/*CL_SlotParent_v0 &*/);
	void first_frame();
	void setCurLevel(int);
	int getOptionsCode();
	void showCredits();


private:
	CL_DisplayWindow *display;
	GameDisplay *myGameDisplay;

	bool is_arrow_up[4];

	bool quit1;
	bool quit2;
	bool quit_splash;
	bool showsplash3;
	bool paused;
	bool fullscreen;
	bool help_on;
	bool show_credits;
	int cur_speed;

	// number of bots earned thus far
	int curEarnedBots;

	gameState_t curState;

	CL_ResourceManager font_resources;

	CL_GUIManager *gui1;
	CL_GUIManager *gui2;
	CL_GUIManager *gui3;

	CL_Surface *button_up_surf;
	CL_Surface *button_down_surf;

	CL_Surface *sound;
	CL_Surface *death;
	CL_Surface *help;
	CL_Surface *speed;

	CL_Label *win_label1;
	CL_Label *win_label2;
	CL_Label *win_label3;
	CL_Label *lose_label1;
	CL_Label *lose_label2;
	CL_Label *level_label;

	CL_Image *lose_button1;
	CL_Image *lose_button2;
	CL_Image *win_button1;
	CL_Image *win_button2;
	CL_Image *win_button3;
	CL_Image *level_button;
	CL_Image *lose_popup;
	CL_Image *win_popup;
	CL_Image *level_popup;

	CL_Image *arrow_left;
	CL_Image *arrow_right;
	CL_Image *arrow_up;
	CL_Image *arrow_down;

	CL_Surface *popup_surf;

	CL_Surface *gui;
	CL_Surface *box;
	CL_Surface *none_active;
	CL_Surface *redirect_active;
	CL_Surface *bomb_active;
	CL_Surface *bridge_active;
	CL_Surface *drill_active;
	CL_Surface *turn_active;
	CL_Surface *wallcrawler_active;
	CL_Surface *swim_active;
	CL_Surface *arrows_none;
	CL_Surface *arrows_up;
	CL_Surface *arrows_down;
	CL_Surface *arrows_left;
	CL_Surface *arrows_right;
	CL_Surface *selected;
	CL_Surface *none_options;
	CL_Surface *turn_options;
	CL_Surface *wallcrawler_options;
	CL_Surface *splashscreen1;
	CL_Surface *splashscreen2;
	CL_Surface *splashscreen3;
	CL_Surface *helpwindow;

	CL_Font font1;
	CL_Font font2;
	//int num_bots;
	int selected_bot;
	int selected_arrow;
	int curLevel;
	int highestLevel;
	bool bot_launched;
	bool first_click_t;
	bool first_click_w;

	int options_code;
	box_t bot1;
	box_t bot2;
	box_t bot3;
	box_t bot4;
	box_t bot5;
	box_t bot6;
	box_t bot7;
	box_t bot8;
	box_t bot9;
	box_t arrow_up_box;
	box_t arrow_down_box;
	box_t arrow_left_box;
	box_t arrow_right_box;

	CL_Rect name_box;
	CL_Rect info_box;
	CL_Rect sound_box;
	CL_Rect death_box;
	CL_Rect help_box;
	CL_Rect slow_box;
	CL_Rect medium_box;
	CL_Rect fast_box;

	//strings for text y'all
	char *redirect_name;
	char *bomb_name;
	char *bridge_name;
	char *turn_name;
	char *swim_name;
	char *drill_name;
	char *push_name;
	char *crawler_name;
	char *bait_name;
	char *redirect_info;
	char *bomb_info;
	char *bridge_info;
	char *caboose_info;
	char *caboose_name;
	char *turn_info;
	char *swim_info;
	char *drill_info;
	char *push_info;
	char *crawler_info;
	char *bait_info;
	char *num_bots_string;
	char *generic_name;
	char *generic_info;
	char *begin_string;
	
	void check_bot_clicked(int, int);
	void bot_clicked(int);
	void draw_bot_boxes();
	void draw_bots();
	void draw_active_box();
	void draw_arrows();
	void draw_options();
	void draw_controls();
	void check_controls(int, int);
	void check_restart(int, int);
	void check_arrows(int, int, bool);
	void arrow_clicked(int);
	void init();
	void init_arrows();
	bool in_box(int, int, box_t);
	void draw_levelGUI(string levelName);
	string describeNewBot(int);


};


#endif // !defined(GameUI_H)
