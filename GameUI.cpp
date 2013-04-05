// GameUI.cpp: implementation of the GameUI class.
//
//////////////////////////////////////////////////////////////////////

#include "GameUI.h"
#include <stdlib.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameUI::GameUI(): paused(false), curLevel(1), curEarnedBots(0), help_on(false), show_credits(false)
{
  //Commented out just for the demo
  //CL_ConsoleWindow console("Team Robot Console", 80, 1000);
  //console.redirect_stdio();

  try 
    {
      CL_SetupCore::init();
      CL_SetupDisplay::init();
      CL_SetupGL::init();
      CL_SetupGUI::init();
      CL_SetupSound::init();
      CL_SetupVorbis::init();

      CL_SoundOutput sound_output(44100);
      snd_player.loadSounds();
      snd_player.loadMusic();

      display = new CL_DisplayWindow("Team Robot", 800, 600, false );
      fullscreen = true;
      //CL_Display::set_fullscreen(800, 600, 32);

      CL_Surface *loading = new CL_Surface("images/ui/loading.png");
      loading->draw(0,0);
      CL_Display::flip();

      cur_speed = 1;

      myGameDisplay = new GameDisplay(this);
		
      // setup mouse
      CL_Slot slot_mouse_down = CL_Mouse::sig_key_down().connect( this, &GameUI::on_button_down);
      CL_Slot slot_mouse_up = CL_Mouse::sig_key_up().connect( this, &GameUI::on_button_press);

      //setup keyboard
      CL_Slot slot_key_down = CL_Keyboard::sig_key_down().connect(this, &GameUI::on_key_press);
		
      // Connect the Window close event
      CL_Slot slot_quit = display->sig_window_close().connect(this, &GameUI::on_quit);
	
      // Create the GUI using the default style
      CL_ResourceManager gui_resources("gui.xml");
      font_resources = CL_ResourceManager("font.xml");

      // Load some fonts from the resource file
      font1 = CL_Font("Font1", &font_resources);
      font2 = CL_Font("Font2", &font_resources);

      // init all pop-up windows
      CL_StyleManager_Silver style(&gui_resources);
      gui1 = new CL_GUIManager(&style);
      gui1->disable_input();

      gui2 = new CL_GUIManager(&style);
      gui2->disable_input();

      gui3 = new CL_GUIManager(&style);
      gui3->disable_input();

      sound = new CL_Surface("images/ui/sound.png");
      death = new CL_Surface("images/ui/death.png");
      help  = new CL_Surface("images/ui/help.png");
      speed = new CL_Surface("images/ui/speed.png");

      popup_surf = new CL_Surface("images/ui/popup.png");

      button_up_surf = new CL_Surface("images/ui/button_up.png");
      button_down_surf = new CL_Surface("images/ui/button_down.png");

      lose_popup = new CL_Image(CL_Point(125, 175), popup_surf, false, gui2);
      lose_button1 = new CL_Image(CL_Point(65, 175), button_up_surf, false, lose_popup);
      lose_button2 = new CL_Image(CL_Point(205, 175), button_up_surf, false, lose_popup);

      lose_label1 = new CL_Label(CL_Point(28,15), "Yes", lose_button1->get_client_area());
      lose_label2 = new CL_Label(CL_Point(30,15), "No", lose_button2->get_client_area());
		
      win_popup = new CL_Image(CL_Point(125, 175), popup_surf, false, gui1);
      win_button1 = new CL_Image(CL_Point(35, 175), button_up_surf, false, win_popup);
      win_button2 = new CL_Image(CL_Point(135, 175), button_up_surf, false, win_popup);
      win_button3 = new CL_Image(CL_Point(235, 175), button_up_surf, false, win_popup);

      level_popup = new CL_Image(CL_Point(125, 180), popup_surf, false, gui3);
      level_button = new CL_Image(CL_Point(135, 180), button_up_surf, false, level_popup);

      win_label1 = new CL_Label(CL_Point(10,15), "Next Level", win_button1->get_client_area());
      win_label2 = new CL_Label(CL_Point(22,15), "Retry", win_button2->get_client_area());
      win_label3 = new CL_Label(CL_Point(26,15), "Quit", win_button3->get_client_area());
		

      level_label = new CL_Label(CL_Point(28,15), "Go!", level_button->get_client_area());

      init_arrows();

      helpwindow = new CL_Surface("images/ui/helpwindow.png");

      // init splashscreen
      splashscreen1 = new CL_Surface("images/ui/splashscreen1.png");
      splashscreen2 = new CL_Surface("images/ui/splashscreen2.png");
      splashscreen3 = new CL_Surface("images/ui/splashscreen3.png");

      int i = 0;
      int splash_time1 = 100;
      int splash_time2 = 200;
      int splash_time3 = 300;
      int splash_time4 = 400;
      int splash_ctr = -1;
      int splash_begin;
      float cur_loc;
      int j = 16;
		
      int x_start = 0;
      int y_start = 0;
		
      quit1 = false;
      quit_splash = false;
      showsplash3 = false;
		
      snd_player.playMusic(THIS_IS_THE_RAINBOW);
      //draw splash screen
      while (!CL_Keyboard::get_keycode(CL_KEY_ESCAPE) && !(quit1) && !(quit_splash)) {
        if (splash_ctr == -1) {
          splash_begin = CL_System::get_time();
        }
        splash_ctr = CL_System::get_time() - splash_begin;
        if (showsplash3) {
          splashscreen3->draw(0,0);
          myGameDisplay->genericbot->draw(CL_Rect(30,0,60,30),
                                          CL_Rect((i+cur_loc-0.3f) * 30, (j) * 30, (i+cur_loc-0.3f) * 30 + 30, (j) * 30 + 30));
        }
        else {
          cur_loc = -1.0f + ((float) splash_ctr / (float) splash_time4);
          splashscreen2->draw(0,0);
          splashscreen1->draw(CL_Rect((i+cur_loc+0.2f)*30,0,800,600), CL_Rect((i+cur_loc+0.2f)*30,0,800,600));

          if (splash_ctr < splash_time1) {
            myGameDisplay->genericbot->draw(CL_Rect(0,90,30,120),
                                            CL_Rect((i+cur_loc) * 30, (j) * 30, (i+cur_loc) * 30 + 30, (j) * 30 + 30));
          }
          else if (splash_ctr < splash_time2) {
            myGameDisplay->genericbot->draw(CL_Rect(30,90,60,120),
                                            CL_Rect((i+cur_loc) * 30, (j) * 30, (i+cur_loc) * 30 + 30, (j) * 30 + 30));
          }
          else if (splash_ctr < splash_time3) {
            myGameDisplay->genericbot->draw(CL_Rect(60,90,90,120),
                                            CL_Rect((i+cur_loc) * 30, (j) * 30, (i+cur_loc) * 30 + 30, (j) * 30 + 30));
          }
          else {
            myGameDisplay->genericbot->draw(CL_Rect(30,90,60,120),
                                            CL_Rect((i+cur_loc) * 30, (j) * 30, (i+cur_loc) * 30 + 30, (j) * 30 + 30));
          }
          if (splash_ctr >= splash_time4) {
            splash_begin = CL_System::get_time();
            i++;
            if (i*30 >= 650)
              showsplash3 = true;
          }
        }
        CL_Display::flip();
        CL_System::sleep(10);
        CL_System::keep_alive();
		
      }
      delete splashscreen1;
      delete splashscreen2;
      delete splashscreen3;
      snd_player.stopMusic(THIS_IS_THE_RAINBOW);


      highestLevel = curLevel;
      // if a level file exists, check what the current level should be
      FILE *fp;
      if ((fp = fopen("tr.dat", "rb")) != NULL) {
        int tempHighestLevel = getw(fp);
        if (tempHighestLevel != EOF) highestLevel = tempHighestLevel;
        fclose(fp);
      }
      if (highestLevel > 30) {
        curLevel = 1;
        highestLevel = 30;
      } else {
        curLevel = highestLevel;
      }

      // read in level
      myGameDisplay->initLevel(curLevel);

      string levelName = myGameDisplay->myBoard->getMapTitle();
      levelName.erase(levelName.end() - 1);
      display->set_title("Team Robot - " + levelName);
      curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

      //font1.draw(CL_Rect(10, 15, 300, 170), levelName);
      //level_label0->set_text(levelName);
      //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
      //gui3->show();
      //gui3->enable_input();
      draw_levelGUI(levelName);
		

      init();

      myGameDisplay->ctr = -1;

      snd_player.playMusic(REVERSE_SONG);
      // Main loop
      while (!CL_Keyboard::get_keycode(CL_KEY_ESCAPE) && !(quit1) && !(show_credits))
        {
          if (!show_credits) {
            gui->draw(600,0);
            //draw_bot_boxes();
            draw_bots();
            draw_arrows();
            draw_active_box();
            draw_controls();
            //draw_options();
				
				
				
            /*if(myGameDisplay->ctr == -1) //first frame of turn
              {	
              //printf("begining of turn\n");
              selected_arrow = 0;
              if (bot_launched)
              {
              selected_bot = -1;
              bot_launched = false;
              }
              }*/
				
            curState = myGameDisplay->show(paused);
				
            if (curState == WIN) {
              //if (!snd_player.isPlaying(REVERSE_SONG)) snd_player.playMusic(REVERSE_SONG);
              gui1->enable_input();
              gui1->show();
              font1.draw(CL_Rect(135, 190, 435, 360), "Your Robotrain is unstoppable!\n\nWhat do you want to do?");
            }
            else if (curState == LOSE) {
              gui2->enable_input();
              gui2->show();
              font1.draw(CL_Rect(135, 190, 435, 360), "Oh no! Disaster struck!\nYour Robotrain has failed.\n\nDo you want to try the level again?");
            }
            else if (gui3->is_input_enabled()) {
              string levelName = myGameDisplay->myBoard->getMapTitle();
              levelName.erase(levelName.end() - 1);
              draw_levelGUI(levelName);
              //gui3->show();
            }
            if (help_on) {
              helpwindow->draw(10,10);
            }

          }
          CL_Display::flip();
          CL_System::sleep(10);
          CL_System::keep_alive();
        }
		
    }
  catch (CL_Error e)
    {
      std::cout << e.message.c_str() << std::endl;
		
      // Display console close message and wait for a key
      //NEEDS TO BE UNCOMMENTED WHEN THE CONSOLE IS BACK
      // console.display_close_message();
    }

}


GameUI::~GameUI()
{
  delete button_up_surf;
  delete button_down_surf;

  delete lose_button1;
  delete lose_button2;
  delete win_button1;
  delete win_button2;
  delete win_button3;
  delete level_button;
  delete lose_popup;
  delete win_popup;
  delete level_popup;

  delete sound;
  delete death;
  delete help;
  delete speed;

  // causes errors when you delete these
  /*delete win_label1;
    delete win_label2;
    delete win_label3;
    delete lose_label1;
    delete lose_label2;*/

  delete popup_surf;

  CL_SetupGL::deinit();
  CL_SetupGUI::deinit();
  CL_SetupDisplay::deinit();
  CL_SetupCore::deinit();
  CL_SetupSound::deinit();
  CL_SetupVorbis::deinit();

  delete myGameDisplay;
  //delete font_resources;
}

void GameUI::first_frame()
{	
  //printf("begining of turn\n");
  /*
    selected_arrow = 0;
    if (bot_launched)
    {
    selected_bot = -1;
    bot_launched = false;
    }
  */
}

void GameUI::next_level(/*CL_SlotParent_v0 &parent_handler*/)
{
  paused = false;
  curLevel++;
  //snd_player.stopMusic(REVERSE_SONG);

  if (curLevel > highestLevel) {
    FILE *fp;
    if ((fp = fopen("tr.dat", "wb"))  != NULL) {
      putw(curLevel, fp);
      highestLevel = curLevel;
      fclose(fp);
    }

  }


  myGameDisplay->initLevel(curLevel);

  string levelName = myGameDisplay->myBoard->getMapTitle();
  levelName.erase(levelName.end() - 1);
  display->set_title("Team Robot - " + levelName);
  curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

  //level_label0->set_text(levelName);
  //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
  //gui3->show();
  //gui3->enable_input();
  draw_levelGUI(levelName);

  selected_bot = -1;
}

void GameUI::restart()
{
  if(paused) {
    paused = false;
    CL_System::resume_time();
  }

  myGameDisplay->initLevel(curLevel);
  //snd_player.stopMusic(REVERSE_SONG);

  string levelName = myGameDisplay->myBoard->getMapTitle();

  levelName.erase(levelName.end() - 1);
  display->set_title("Team Robot - " + levelName);
  curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

  //level_label0->set_text(levelName);
  //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
  //gui3->show();
  //gui3->enable_input();
  draw_levelGUI(levelName);

  selected_bot = -1;
  first_click_t = false;
  first_click_w = false;

}

void GameUI::on_close_2(/*CL_SlotParent_v0 &parent_handler*/)
{
  //parent_handler();	// Close window
  quit1 = true;
}

void GameUI::on_quit()
{
  quit1 = quit2 = true;
}

void GameUI::on_key_press(const CL_InputEvent &key)
{
  string levelName;

  //Full screen mode should be available at any time
  if((key.id == CL_KEY_ENTER) && (CL_Keyboard::get_keycode(CL_KEY_LMENU) || CL_Keyboard::get_keycode(CL_KEY_RMENU))) {
    if (fullscreen) {
      CL_Display::set_windowed();
      CL_Display::set_size(800, 600);
    } else {
      CL_Display::set_fullscreen(800, 600, 32);
    }
    fullscreen = !fullscreen;
  }


  if (!(gui1->is_input_enabled() || gui2->is_input_enabled() || gui3->is_input_enabled()) && quit_splash && !show_credits) {
    switch(key.id) {

    case CL_KEY_UP:
      arrow_clicked(1);
      break;

    case CL_KEY_W:
      arrow_clicked(1);
      break;

    case CL_KEY_DOWN:
      arrow_clicked(2);
      break;

    case CL_KEY_S:
      arrow_clicked(2);
      break;

    case CL_KEY_LEFT:
      arrow_clicked(3);
      break;

    case CL_KEY_A:
      arrow_clicked(3);
      break;

    case CL_KEY_RIGHT:
      arrow_clicked(4);
      break;

    case CL_KEY_D:
      arrow_clicked(4);
      break;

    case CL_KEY_NUMPAD7:
      if(curEarnedBots > 0) {
        bot_clicked(REDIRECTBOT);
      }
      break;
    case CL_KEY_NUMPAD8:
      if(curEarnedBots > 1) {
        bot_clicked(BOMBBOT);
      }
      break;
    case CL_KEY_NUMPAD9:
      if(curEarnedBots > 2) {
        bot_clicked(BRIDGEBOT);
      }
      break;
    case CL_KEY_NUMPAD4:
      if(curEarnedBots > 3) {
        bot_clicked(TURNBOT);
      }
      break;
    case CL_KEY_NUMPAD5:
      if(curEarnedBots > 4) {
        bot_clicked(SWIMBOT);
      }
      break;
    case CL_KEY_NUMPAD6:
      if(curEarnedBots > 5) {
        bot_clicked(DRILLBOT);
      }
      break;
    case CL_KEY_NUMPAD1:
      if(curEarnedBots > 6) {
        bot_clicked(PUSHBOT);
      }
      break;
    case CL_KEY_NUMPAD2:
      if(curEarnedBots > 7) {
        bot_clicked(WALLCRAWLER);
      }
      break;
    case CL_KEY_NUMPAD3:
      if(curEarnedBots > 8) {
        bot_clicked(DECOYBOT);
      }
      break;
    default:
      break;
    }
  }

  if (quit_splash && !show_credits) {
    switch(key.id) {
      //nasty hacks to be changed
    case CL_KEY_NEXT:
      if (curLevel < highestLevel) {
        curLevel++;
        myGameDisplay->initLevel(curLevel);

        levelName = myGameDisplay->myBoard->getMapTitle();
        levelName.erase(levelName.end() - 1);
        display->set_title("Team Robot - " + levelName);
        curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

        //level_label0->set_text(levelName);
        //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
        //gui3->show();
        //gui3->enable_input();
        draw_levelGUI(levelName);
        if(paused) {
          paused = false;
          CL_System::resume_time();
        }
        selected_bot = -1;
      }
      break;

    case CL_KEY_PRIOR:
      curLevel--;
      myGameDisplay->initLevel(curLevel);

      levelName = myGameDisplay->myBoard->getMapTitle();
      levelName.erase(levelName.end() - 1);
      display->set_title("Team Robot - " + levelName);
      curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

      //level_label0->set_text(levelName);
      //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
      //gui3->show();
      //gui3->enable_input();
      draw_levelGUI(levelName);
      if(paused) {
        paused = false;
        CL_System::resume_time();
      }
      selected_bot = -1;
      break;

      //Removed for release versions
      /*	
		case CL_KEY_5:
                curLevel = 15;
                myGameDisplay->initLevel(curLevel);

                levelName = myGameDisplay->myBoard->getMapTitle();
                levelName.erase(levelName.end() - 1);
                display->set_title("Team Robot - " + levelName);
                curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

                //level_label0->set_text(levelName);
                //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
                //gui3->show();
                //gui3->enable_input();
                draw_levelGUI(levelName);

                selected_bot = -1;
                break;

		case CL_KEY_6:
                curLevel = 25;
                myGameDisplay->initLevel(curLevel);

                levelName = myGameDisplay->myBoard->getMapTitle();
                levelName.erase(levelName.end() - 1);
                display->set_title("Team Robot - " + levelName);
                curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

                //level_label0->set_text(levelName);
                //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
                //gui3->show();
                //gui3->enable_input();
                draw_levelGUI(levelName);

                selected_bot = -1;
                break;*/
    default:
      break;
    }
  }
}

void GameUI::on_button_press(const CL_InputEvent &key)
{
  int x,y;
  string levelName;

  if (!show_credits) {
    switch(key.id) {

    case CL_MOUSE_LEFT:
			
      x = key.mouse_pos.x;
      y = key.mouse_pos.y;

      //printf("%d,%d\n",x,y);

      if (help_on) {
        help_on = false;
      }
      else {
        if (quit_splash) {
          check_controls(x,y);
        }
        // if game win or lose popup windows are visible, see if their buttons were clicked
        if (gui2->is_input_enabled()) {
					
          if (((lose_button1->get_screen_rect()).is_inside(CL_Point(x, y)) || (lose_label1->get_screen_rect()).is_inside(CL_Point(x, y))) && lose_button1->get_surface() == button_down_surf) {
            gui2->disable_input();
            //gui3->show();
            gui3->enable_input();
            restart();
          }
          else if (((lose_button2->get_screen_rect()).is_inside(CL_Point(x, y)) || (lose_label2->get_screen_rect()).is_inside(CL_Point(x, y))) && lose_button2->get_surface() == button_down_surf) {
            gui2->disable_input();
            on_close_2();
          }
          lose_button1->set_surface(button_up_surf);
          lose_button2->set_surface(button_up_surf);
        }
        else if (gui1->is_input_enabled()) {
					
          if (((win_button1->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label1->get_screen_rect()).is_inside(CL_Point(x, y))) && win_button1->get_surface() == button_down_surf) {
            gui1->disable_input();
            //gui3->show();
            gui3->enable_input();
            next_level();
          }
          else if (((win_button2->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label2->get_screen_rect()).is_inside(CL_Point(x, y))) && win_button2->get_surface() == button_down_surf) {
            gui1->disable_input();
            //gui3->show();
            gui3->enable_input();
            restart();
          }
          else if (((win_button3->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label3->get_screen_rect()).is_inside(CL_Point(x, y))) && win_button3->get_surface() == button_down_surf) {
            gui1->disable_input();
            on_close_2();
          }
          win_button1->set_surface(button_up_surf);
          win_button2->set_surface(button_up_surf);
          win_button3->set_surface(button_up_surf);
        }
        else if (gui3->is_input_enabled()) {
					
          if (((level_button->get_screen_rect()).is_inside(CL_Point(x, y)) || (level_label->get_screen_rect()).is_inside(CL_Point(x, y))) && level_button->get_surface() == button_down_surf) {
            gui3->disable_input();
          }
          level_button->set_surface(button_up_surf);
        }
        else if (!quit_splash) {
          quit_splash = true;
          showsplash3 = false;
        }
        else {
          check_bot_clicked(x,y);
          check_arrows(x,y, true);
          check_restart(x,y);
        }
				
      }
      break;

    case CL_MOUSE_MIDDLE:
		
      break;

    case CL_MOUSE_RIGHT:
      if (!(gui1->is_input_enabled() || gui2->is_input_enabled() || gui3->is_input_enabled()) && quit_splash && !help_on) {
        paused = !paused;
        if (paused) {
          CL_System::suspend_time();
        }
        else {
          CL_System::resume_time();
        }
      }
	
      break;

    case CL_MOUSE_XBUTTON1:
			
      break;

    case CL_MOUSE_XBUTTON2:

      break;
      //Took this out for the release because it seems hacky
      /*
        case CL_MOUSE_WHEEL_UP:
        if (!(gui1->is_input_enabled() || gui2->is_input_enabled() || gui3->is_input_enabled()) && quit_splash) {
        myGameDisplay->initLevel(curLevel);
        levelName = myGameDisplay->myBoard->getMapTitle();
        levelName.erase(levelName.end() - 1);
        display->set_title("Team Robot - " + levelName);
        curEarnedBots = myGameDisplay->myBoard->getEarnedBots();

        //level_label0->set_text(levelName);
        //level_label2->set_text(myGameDisplay->myBoard->getNumberOfBots());
        //gui3->show();
        //gui3->enable_input();
        draw_levelGUI(levelName);

        selected_bot = -1;
        first_click_t = false;
        first_click_w = false;

        if(paused) {
        paused = false;
        CL_System::resume_time();
        }
        }

        break;*/

    case CL_MOUSE_WHEEL_DOWN:
			
    default:
      break;
    }
  }
}

void GameUI::showCredits() {
  int time_begin = CL_System::get_time();
  int cur_time;
  int max_time = 70000;
  show_credits = true;
  //string credits = "Team Robot is...\n\n";
  CL_Surface *credits = new CL_Surface("images/ui/credits.png");
  float y = 2300.0f;
  snd_player.stopMusic(REVERSE_SONG);
  snd_player.playMusic(THIS_IS_THE_RAINBOW);
  while (y > 0.0f && !CL_Keyboard::get_keycode(CL_KEY_ESCAPE) && !(quit1)) {
    cur_time = CL_System::get_time() - time_begin;
    y = 2300.0f - (float) cur_time / (float) max_time * 2300.0f;


    CL_Display::clear();

    credits->draw(0,y - 1700.0f);

    CL_Display::flip();
    CL_System::sleep(10);
    CL_System::keep_alive();
  }
  show_credits = false;
  delete credits;
}

void GameUI::on_button_down(const CL_InputEvent &key)
{
  int x,y;
  x = key.mouse_pos.x;
  y = key.mouse_pos.y;
  //printf("1 %i, 2 %i\n", gui1->is_input_enabled(), gui2->is_input_enabled());
  //printf("one: %i, two: %i, three: %i\n", (win_button1->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label1->get_screen_rect()).is_inside(CL_Point(x, y)), 
  //	(win_button2->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label2->get_screen_rect()).is_inside(CL_Point(x, y)), (win_button3->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label3->get_screen_rect()).is_inside(CL_Point(x, y)));
  if (!show_credits) {
    switch(key.id) {

    case CL_MOUSE_LEFT:

      // if game win or lose popup windows are visible, see if their buttons were clicked
      if (!help_on) {
        if (gui3->is_input_enabled())
          {
            if ((level_button->get_screen_rect()).is_inside(CL_Point(x, y))
                || (level_label->get_screen_rect()).is_inside(CL_Point(x, y))) {
              level_button->set_surface(button_down_surf);
            }
          }
        else if (gui2->is_input_enabled())
          {
            if ((lose_button1->get_screen_rect()).is_inside(CL_Point(x, y)) || (lose_label1->get_screen_rect()).is_inside(CL_Point(x, y))) {
              lose_button1->set_surface(button_down_surf);
            }
            else if ((lose_button2->get_screen_rect()).is_inside(CL_Point(x, y)) || (lose_label2->get_screen_rect()).is_inside(CL_Point(x, y))) {
              lose_button2->set_surface(button_down_surf);
            }
          }
        else if (gui1->is_input_enabled()) {
          if ((win_button1->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label1->get_screen_rect()).is_inside(CL_Point(x, y))) {
            win_button1->set_surface(button_down_surf);
          }
          else if ((win_button2->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label2->get_screen_rect()).is_inside(CL_Point(x, y))) {
            win_button2->set_surface(button_down_surf);
          }
          else if ((win_button3->get_screen_rect()).is_inside(CL_Point(x, y)) || (win_label3->get_screen_rect()).is_inside(CL_Point(x, y))) {
            win_button3->set_surface(button_down_surf);
          }
        } else {  
          check_arrows(x, y, false);
        }
      }

      break;

    default:
			
      break;
    }
  }
}

/*void GameUI::on_quit()
  {
  quit1 = true;
  }*/

/* checks to see if any launch arrows were clicked*/
void GameUI::check_arrows(int x, int y, bool up)
{
  if (up) {
    for (int i = 0; i < 4; i++) {
      is_arrow_up[i] = true;
    }
    if (in_box(x, y, arrow_up_box)) {
      arrow_clicked(1);
    }
    else if (in_box(x, y, arrow_down_box)) {
      arrow_clicked(2);
    }
    else if (in_box(x, y, arrow_left_box)) {
      arrow_clicked(3);
    }
    else if (in_box(x, y, arrow_right_box)) {
      arrow_clicked(4);
    }
  } else {
    if (in_box(x, y, arrow_up_box)) {
      is_arrow_up[0] = false;
    }
    else if (in_box(x, y, arrow_down_box)) {
      is_arrow_up[1] = false;
    }
    else if (in_box(x, y, arrow_left_box)) {
      is_arrow_up[2] = false;
    }
    else if (in_box(x, y, arrow_right_box)) {
      is_arrow_up[3] = false;
    }

  }

}

// and bot info
void GameUI::draw_controls() {

  std::stringstream ss;

  if (snd_player.isMuted()) 
    sound->draw(CL_Rect(25, 0, 50, 25), sound_box);  
  else 
    sound->draw(CL_Rect(0, 0, 25, 25), sound_box);  

  death->draw(CL_Rect(0, 0, 25, 25), death_box);
  help->draw(CL_Rect(0, 0, 25, 25), help_box);

  ss << "Generic Bots: " << myGameDisplay->myBoard->getBotsLeft()
     << "/" << myGameDisplay->myBoard->getNumberOfBots();

  font1.draw(618,440, ss.str());

  if(cur_speed == 0) speed->draw(CL_Rect(86, 0, 172, 19), slow_box);
  else speed->draw(CL_Rect(0, 0, 85, 19), slow_box);
  if (cur_speed == 1) speed->draw(CL_Rect(86, 20, 172, 42), medium_box);
  else speed->draw(CL_Rect(0, 20, 85, 42), medium_box);
  if (cur_speed == 2) speed->draw(CL_Rect(86, 43, 172, 65), fast_box);
  else speed->draw(CL_Rect(0, 43, 85, 65), fast_box);

}

void GameUI::check_controls(int x, int y) {
  float ratio;

  if (sound_box.is_inside(CL_Point(x, y))) {
    snd_player.mute();
    if (snd_player.isMuted()) {
      snd_player.stopAllMusic();
      snd_player.stopAllSounds();
    } else {
      snd_player.playMusic(REVERSE_SONG);
    }
  } else if (slow_box.is_inside(CL_Point(x, y))) {
    cur_speed = 0;
    ratio = (float)myGameDisplay->ctr / (float)myGameDisplay->time4;
    myGameDisplay->time1 = 350;
    myGameDisplay->time2 = 700;
    myGameDisplay->time3 = 1050;
    myGameDisplay->time4 = 1400;
    myGameDisplay->time_ctr = myGameDisplay->time4 / 13;
    myGameDisplay->ctr = (int)(ratio * myGameDisplay->time4);
    myGameDisplay->begin_time = CL_System::get_time() - myGameDisplay->ctr;
  } else if (medium_box.is_inside(CL_Point(x, y))) {
    cur_speed = 1;
    ratio = (float)myGameDisplay->ctr / (float)myGameDisplay->time4;
    myGameDisplay->time1 = 250;
    myGameDisplay->time2 = 500;
    myGameDisplay->time3 = 750;
    myGameDisplay->time4 = 1000;
    myGameDisplay->time_ctr = myGameDisplay->time4 / 13;
    myGameDisplay->ctr = (int)(ratio * myGameDisplay->time4);
    myGameDisplay->begin_time = CL_System::get_time() - myGameDisplay->ctr;
  } else if (fast_box.is_inside(CL_Point(x, y))) {
    cur_speed = 2;
    ratio = (float)myGameDisplay->ctr / (float)myGameDisplay->time4;
    myGameDisplay->time1 = 150;
    myGameDisplay->time2 = 300;
    myGameDisplay->time3 = 450;
    myGameDisplay->time4 = 600;
    myGameDisplay->time_ctr = myGameDisplay->time4 / 13;
    myGameDisplay->ctr = (int)(ratio * myGameDisplay->time4);
    myGameDisplay->begin_time = CL_System::get_time() - myGameDisplay->ctr;
  }
	
  else if (help_box.is_inside(CL_Point(x, y))) {
    help_on = true;
    if(!paused && first_arrow_clicked) {
      paused = true;
      CL_System::suspend_time();
    }
  }
}

void GameUI::check_restart(int x, int y) {
  if (death_box.is_inside(CL_Point(x, y))) {
    //Took this out because it's annoying if after you click restart
    //it asks you if you want to try again.  Obviously yes.
    //myGameDisplay->myBoard->setExplodeAll(true);
    restart();
  }
}

void GameUI::draw_arrows()
{
  //if(selected_arrow == 0)
  //	;//arrows_none->draw(750,317);
  if (is_arrow_up[0]) arrows_up->draw(CL_Rect(0,30,94,60), CL_Rect(653,246,653+94,246+30));
  else arrows_up->draw(CL_Rect(0,60,94,90), CL_Rect(653,246,653+94,246+30));
	
  if (is_arrow_up[1]) arrows_down->draw(CL_Rect(0,30,94,60), CL_Rect(653,383,653+94,383+30));
  else arrows_down->draw(CL_Rect(0,60,94,90), CL_Rect(653,383,653+94,383+30));

  if (is_arrow_up[2]) arrows_left->draw(CL_Rect(30,0,60,94), CL_Rect(616,283,616+30,283+94));
  else arrows_left->draw(CL_Rect(60,0,90,94), CL_Rect(616,283,616+30,283+94));

  if (is_arrow_up[3]) arrows_right->draw(CL_Rect(30,0,60,94), CL_Rect(754,283,754+30,283+94));
  else arrows_right->draw(CL_Rect(60,0,90,94), CL_Rect(754,283,754+30,283+94));

  /*
    if(selected_arrow == 1)
    arrows_up->draw(CL_Rect(0,60,94,90), CL_Rect(653,246,653+94,246+30));

    if(selected_arrow == 2)
    arrows_down->draw(CL_Rect(0,60,94,90), CL_Rect(653,383,653+94,383+30));

    if(selected_arrow == 3)
    arrows_left->draw(CL_Rect(60,0,90,94), CL_Rect(616,283,616+30,283+94));

    if(selected_arrow == 4)
    arrows_right->draw(CL_Rect(60,0,90,94), CL_Rect(754,283,754+30,283+94));
  */
}

void GameUI::init_arrows() {/*
                              arrows_left = new CL_Surface("images/ui/arrow_left.png");
                              arrows_right = new CL_Surface("images/ui/arrow_right.png");
                              arrows_up = new CL_Surface("images/ui/arrow_up.png");
                              arrows_down = new CL_Surface("images/ui/arrow_down.png");*/
  for (int i = 0; i < 4; i++) {
    is_arrow_up[i] = true;
  }
}

void GameUI::draw_options()
{
  none_options->draw(645,371);

  if (selected_bot == TURNBOT)
    turn_options->draw(645,371);

  if (selected_bot == WALLCRAWLER)
    wallcrawler_options->draw(645,371);
}


/* called when an arrow is clicked */
void GameUI::arrow_clicked(int arrow_num)
{
  first_arrow_clicked = true;
  //printf("arrow %d clicked\n",arrow_num);
  //selected_arrow = arrow_num;
  first_click_t = false;
  first_click_w = false;

  myGameDisplay->myBoard->addToLaunchBehaviorList((behavior_t) options_code); //fix this eventually
  myGameDisplay->myBoard->addToLaunchDirectionList((direction_t) (arrow_num - 1));

  selected_bot = -1;
  /*
    if( selected_bot != -1)
    {
    //myGameDisplay->myBoard->setLaunch(true);
    //myGameDisplay->myBoard->setCurBotType((moveable_t) selected_bot);
    //myGameDisplay->myBoard->addToLaunchBehaviorList((behavior_t) options_code); //fix this eventually
    //bot_launched = true;
    }*/
}

/* checks to see if a bot was clicked; calls bot_clicked if necessary*/
void GameUI::check_bot_clicked(int x, int y)
{
  /* we need to check and see if each square where there could be a bot
     is clicked, but only if they have that bot*/
  if(curEarnedBots > 0) {
    if(in_box(x, y, bot1))
      bot_clicked(REDIRECTBOT);
		
    else if(curEarnedBots > 1) {
      if(in_box(x, y, bot2))
        bot_clicked(BOMBBOT);
			
      else if(curEarnedBots > 2) {
        if(in_box(x, y, bot3))
          bot_clicked(BRIDGEBOT);
				
        else if(curEarnedBots > 3) {
          if(in_box(x, y, bot4))
            bot_clicked(TURNBOT);
					
          else if(curEarnedBots > 4) {
            if(in_box(x, y, bot5))
              bot_clicked(SWIMBOT);
						
            else if(curEarnedBots > 5) {
              if(in_box(x, y, bot6))
                bot_clicked(DRILLBOT);
							
              else if(curEarnedBots > 6) {
                if(in_box(x, y, bot7))
                  bot_clicked(PUSHBOT);
								
                else if(curEarnedBots > 7) {
                  if(in_box(x, y, bot8))
                    bot_clicked(WALLCRAWLER);
									
                  else if(curEarnedBots > 8) {
                    if(in_box(x, y, bot9))
                      bot_clicked(DECOYBOT);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

/* gets called when a bot is clicked
   takes in the enum of the bot clicked*/
void GameUI::bot_clicked(int bot)
{
  if (first_arrow_clicked && myGameDisplay->myBoard->getBotsLeft() > 0)
    {
      if(bot == REDIRECTBOT)
	{
          selected_bot = REDIRECTBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(REDIRECTBOT);
	}
	
      if(bot == BOMBBOT)
	{
          selected_bot = BOMBBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(BOMBBOT);
	}
	
      if(bot == BRIDGEBOT)
	{
          selected_bot = BRIDGEBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(BRIDGEBOT);
	}

      if(bot == DRILLBOT)
	{
          selected_bot = DRILLBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(DRILLBOT);
	}

      if(bot == SWIMBOT)
	{
          selected_bot = SWIMBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(SWIMBOT);
	}

      if(bot == TURNBOT)
	{
          selected_bot = TURNBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(TURNBOT);
          first_click_t = !first_click_t;

          if(first_click_t)
            {
              options_code = TURNLEFT;
              //printf("turn left\n");
            }
          else
            {
              options_code = TURNRIGHT;
              //printf("turn right\n");
            }

		
	}

	
      if(bot == PUSHBOT)
	{
          selected_bot = PUSHBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(PUSHBOT);
	}

      if(bot == WALLCRAWLER)
	{
          selected_bot = WALLCRAWLER;
          myGameDisplay->myBoard->getFrontBot()->setType(WALLCRAWLER);
          first_click_w = !first_click_w;
		
          if(first_click_w)
            {
              options_code = LEFTSIDE;
              //printf("wall on left\n");
            }
          else
            {
              options_code = RIGHTSIDE;
              //printf("wall on right\n");
            }

	}

      if(bot == DECOYBOT)
	{
          //printf("decoy bot selected\n");
          selected_bot = DECOYBOT;
          myGameDisplay->myBoard->getFrontBot()->setType(DECOYBOT);
	}
    }
}

/* draws the boxes where the bots are to go; a box is 32x32 pixels*/
void GameUI::draw_bot_boxes()
{

  int i;

  for (i=0; i < 5; i++)
    box->draw(620 + i*32, 265);

  for (i=0; i < 5; i++)
    box->draw(620 + i*32, 297);

}

/* draws the available bots on the selection screen*/
void GameUI::draw_bots()
{
  switch (curEarnedBots) { // switch statement falls through for all cases
  case 9:
    myGameDisplay->decoybot->draw(CL_Rect(30,0,60,30), CL_Rect(717,347,717+30,347+30));
  case 8:
    if (options_code == RIGHTSIDE && selected_bot == WALLCRAWLER) {
      myGameDisplay->wallcrawler_right->draw(CL_Rect(30,0,60,30), CL_Rect(685,347,685+30,347+30));
    }
    else {
      myGameDisplay->wallcrawler_left->draw(CL_Rect(30,0,60,30), CL_Rect(685,347,685+30,347+30));
    }
  case 7:
    myGameDisplay->pushbot->draw(CL_Rect(30,0,60,30), CL_Rect(653,347,653+30,347+30));
  case 6:
    myGameDisplay->drillbot->draw(CL_Rect(30,0,60,30), CL_Rect(717,315,717+30,315+30));
  case 5:
    myGameDisplay->swimbot->draw(CL_Rect(30,0,60,30), CL_Rect(685,315,685+30,315+30));
  case 4:
    if (options_code == TURNRIGHT && selected_bot == TURNBOT) {
      myGameDisplay->turnbot_right->draw(CL_Rect(30,0,60,30), CL_Rect(653,315,653+30,315+30));
    }
    else {
      myGameDisplay->turnbot_left->draw(CL_Rect(30,0,60,30), CL_Rect(653,315,653+30,315+30));
    }
  case 3:	
    myGameDisplay->bridgebot->draw(CL_Rect(30,0,60,30), CL_Rect(717,283,717+30,283+30));
  case 2:
    myGameDisplay->bombbot->draw(CL_Rect(30,0,60,30), CL_Rect(685,283,685+30,283+30));
  case 1:
    myGameDisplay->arrowbot->draw(CL_Rect(30,0,60,30), CL_Rect(653,283,653+30,283+30));
    break;
  default:
    printf("Error - undefined value for curEarnedBots in GameUI.cpp\n");
    break;
  }
}

void GameUI::draw_active_box()
{
	
  if(selected_bot == -1)
    {
		
      if(first_arrow_clicked)
        {
          if(myGameDisplay->myBoard->getBotsLeft() == 0) {
            font2.draw(name_box, caboose_name);
            font1.draw(info_box, caboose_info);
          }
          else {
            //this would be the generic bot
            font2.draw(name_box, generic_name);
            font1.draw(info_box, generic_info);
          }
        }
      else
        font2.draw(name_box, begin_string);
    }

  if(selected_bot == REDIRECTBOT)
    {
      selected->draw(653,283);
      font2.draw(name_box, redirect_name);
      font1.draw(info_box, redirect_info);
    }
	
  if(selected_bot == BOMBBOT)
    {
      selected->draw(685,283);
      font2.draw(name_box, bomb_name);
      font1.draw(info_box, bomb_info);
    }
	
  if(selected_bot == BRIDGEBOT)
    {	
      selected->draw(717, 283);
      font2.draw(name_box, bridge_name);
      font1.draw(info_box, bridge_info);
    }

  if(selected_bot == TURNBOT)
    {	
      selected->draw(653,315);
      font2.draw(name_box, turn_name);
      font1.draw(info_box, turn_info);
    }

  if(selected_bot == SWIMBOT)
    {	
      selected->draw(685,315);
      font2.draw(name_box, swim_name);
      font1.draw(info_box, swim_info);
    }

  if(selected_bot == DRILLBOT)
    {	
      selected->draw(717,315);
      font2.draw(name_box, drill_name);
      font1.draw(info_box, drill_info);
    }

  if(selected_bot == PUSHBOT)
    {
      selected->draw(653,347);
      font2.draw(name_box, push_name);
      font1.draw(info_box, push_info);
    }

  if(selected_bot == WALLCRAWLER)
    {	
      selected->draw(685,347);
      font2.draw(name_box, crawler_name);
      font1.draw(info_box, crawler_info);
    }
	
  if(selected_bot == DECOYBOT)
    {	
      selected->draw(717,347);
      font2.draw(name_box, bait_name);
      font1.draw(info_box, bait_info);
    }
}

void GameUI::init()
{
	
  //num_bots = 8;
  selected_bot = -1;
  //selected_arrow = 0;
  first_click_t = false;
  first_click_w = false;
  first_arrow_clicked = false;

  bot1.x = 652;
  bot1.y = 282;
  bot1.width = 32;
  bot1.height = 32;
	
  bot2.x = 684;
  bot2.y = 282;
  bot2.width = 32;
  bot2.height = 32;
	
  bot3.x = 716;
  bot3.y = 282;
  bot3.width = 32;
  bot3.height = 32;
	
  bot4.x = 652;
  bot4.y = 314;
  bot4.width = 32;
  bot4.height = 32;

  bot5.x = 684;
  bot5.y = 314;
  bot5.width = 32;
  bot5.height = 32;

  bot6.x = 716;
  bot6.y = 314;
  bot6.width = 32;
  bot6.height = 32;

  bot7.x = 652;
  bot7.y = 347;
  bot7.width = 32;
  bot7.height = 32;

  bot8.x = 684;
  bot8.y = 347;
  bot8.width = 32;
  bot8.height = 32;

  bot9.x = 716;
  bot9.y = 347;
  bot9.width = 32;
  bot9.height = 32;

  arrow_up_box.x = 653;
  arrow_up_box.y = 246;
  arrow_up_box.width = 94;
  arrow_up_box.height = 30;

  arrow_down_box.x = 653;
  arrow_down_box.y = 383;
  arrow_down_box.width = 94;
  arrow_down_box.height = 30;

  arrow_left_box.x = 616;
  arrow_left_box.y = 283;
  arrow_left_box.width = 30;
  arrow_left_box.height = 94;

  arrow_right_box.x = 754;
  arrow_right_box.y = 283;
  arrow_right_box.width = 30;
  arrow_right_box.height = 94;


  gui = new CL_Surface("images/ui/teamrobotgui.png");
  selected = new CL_Surface("images/ui/selected.png");
  arrows_up = new CL_Surface("images/ui/arrow_up.png");
  arrows_down = new CL_Surface("images/ui/arrow_down.png");
  arrows_left = new CL_Surface("images/ui/arrow_left.png");
  arrows_right = new CL_Surface("images/ui/arrow_right.png");


  name_box = CL_Rect(620, 20, 780, 80);
  info_box = CL_Rect(624, 82, 773, 217);

  CL_Point controls = CL_Point(612, 552);
  sound_box = CL_Rect(0, 0, 25, 25) + controls;
  death_box = CL_Rect(0, 0, 25, 25) + controls + CL_Point(30, 0);
  help_box = CL_Rect(0, 0, 25, 25) + controls + CL_Point(60, 0);
	
  CL_Point slow_point = CL_Point(612, 470);
  CL_Point medium_point = CL_Point(0, 20) + slow_point;
  CL_Point fast_point = CL_Point(0, 23) + medium_point;
  slow_box = CL_Rect(0, 0, 85, 20) + slow_point;
  medium_box = CL_Rect(0, 0, 85, 23) + medium_point;
  fast_box = CL_Rect(0, 0, 85, 23) + fast_point;

  //text
	
  redirect_name = "Redirection Bot";
  bomb_name = "Bomb Bot";
  bridge_name = "Bridge Bot";
  turn_name = "Turn Bot";
  swim_name = "Swim Bot";
  drill_name = "Drill Bot";
  push_name = "Push Bot";
  crawler_name = "Wallcrawler";
  bait_name = "Decoy Bot";
  generic_name = "Generic Bot";
  caboose_name = "Caboose Bot";
  redirect_info = "Turns the square beneath it into a redirection arrow for your train. Set the direction with the launch arrows.";
  bomb_info = "Walks until it collides with a wall, then explodes, destroying any continuous groups of bombable crates. Can also be used to destroy Alien Bots.";
  bridge_info = "Walks until it encounters water or lava and then creates a bridge for your Robotrain.";
  turn_info = "Walks until it hits a wall and then turns either right or left, following its blinking shoulder. Change the blinking shoulder by clicking again. Will not turn to avoid lava or water.";
  swim_info = "Walks in a line swimming through any water in its way.";
  drill_info = "Walks in a line destroying any drillable terrain in its way.";
  push_info = "Walks in a line pushing heavy blocks in its way. It explodes when it cannot push any further.";
  crawler_info = "Walks in a line until it hits a wall. Then turns and walks whichever way keeps its outstretched hand in contact with the wall. Change outstretched hand by clicking again.";
  bait_info = "Walks in a line until it hits a wall and then attracts Alien Bots.";
  generic_info = "Walks in a line. Click any other Bot in the selection panel to tentatively transform into that Bot. Transformation is not complete until you launch the new Bot."; 
  caboose_info = "Can only walk in a line.  Cannot be transformed or launched.  Get this Bot to the finish to beat the level!";
  num_bots_string = "temp";
  begin_string = "Click an arrow to launch train!";

}

/* returns whether a given mouse coordinates is in a given box*/
bool GameUI::in_box(int x, int y, box_t box)
{
  //printf("%d,%d, %d,%d,%d,%d\n", x, y, box.x, box.y, box.height, box.width);
  return (x > box.x && x < box.x + box.width && y > box.y && y < box.y + box.height);

}

void GameUI::draw_levelGUI(string levelName) {
  gui3->enable_input();
  gui3->show();
  if (!(myGameDisplay->myBoard->getNewBot())) { // if no new bots in this level
    font2.draw(CL_Rect(135, 190, 435, 360), levelName);
    std::stringstream ss;
    ss << "Generic Bots Available:  "
       << myGameDisplay->myBoard->getNumberOfBots()
       << "\n\n" << myGameDisplay->myBoard->getLevelDescription();
    font1.draw(CL_Rect(135, 220, 445, 360), ss.str());
  }
  else {
    std::stringstream ss;
    font2.draw(CL_Rect(135, 190, 435, 360), levelName);
    ss << "Generic Bots Available:  " 
       << myGameDisplay->myBoard->getNumberOfBots()
       << describeNewBot(curEarnedBots) 
       << "\n\n" <<  myGameDisplay->myBoard->getLevelDescription();
    font1.draw(CL_Rect(135, 220, 445, 360), ss.str());
  }
}

string GameUI::describeNewBot(int earnedBot) {
  CL_Rect draw_dest(440,185,440+30,185+30);
  switch (earnedBot) {

  case 1: // redirection bot
    myGameDisplay->arrowbot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nYou have a Redirection Bot!";

  case 2: // bomb bot
    myGameDisplay->bombbot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Bomb Bot!";

  case 3: // bridge bot
    myGameDisplay->bridgebot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Bridge Bot!";

  case 4: // turn bot
    myGameDisplay->turnbot_left->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Turn Bot!";

  case 5: // swim bot
    myGameDisplay->swimbot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Swim Bot!";

  case 6: // drill bot
    myGameDisplay->drillbot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Drill Bot!";

  case 7: // push bot
    myGameDisplay->pushbot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Push Bot!";

  case 8: // wallcrawler
    myGameDisplay->wallcrawler_left->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Wallcrawler Bot!";

  case 9: // decoy bot
    myGameDisplay->decoybot->draw(CL_Rect(30,0,60,30), draw_dest);
    return "\n\nCongratulations, you have earned the Decoy Bot!";

  default:
    return "";
  }
}

void GameUI::setCurLevel(int curLevelp) {
  curLevel = curLevelp;
}

int GameUI::getOptionsCode() {
  return options_code;
}

class App : public CL_ClanApplication
{
public:
  int main(int argc, char** argv)
  { 
    try 
      {
        GameUI ui;
      }
    catch (CL_Error e)
      {
        printf("error\n");
      }
    
    return 0;
  }

} app;
