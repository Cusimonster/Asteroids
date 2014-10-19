// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Spacewar";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  768;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

const int MAX_BULLETS = 50;
const float SHIP_SHOOT_DELAY = 0.8;
const int MAX_ASTEROIDS = 50;
const float ASTEROID_ROTATION_SPEED = 0.003;
const float ASTEROID_SPAWN_DELAY = 0.4;
const int MAX_GUNS = 7;
const float GUN_SHOOT_DELAY = 4.0;
const int MAX_ENEMY_BULLETS = 50;

// graphic images
const char SPACE_IMAGE[] =    "pictures\\background.png";
const char BULLET_IMAGE[] =		"pictures\\bullet.png";
const char ENEMY_BULLET_IMAGE[] = "pictures\\enemybullet.png";
const char SHIP_IMAGE[] =	   "pictures\\Ship.png";
const char ASTEROID_IMAGE[] = "pictures\\asteroid.png";
const char GUN_IMAGE[] =	"pictures\\asteroidGun.png";


//text messages
const char GAME_OVER_MESSAGE[] = "Game Over...";



// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\WavesExample1.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";

// audio cues
const char BEEP1[] = "beep1";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[]   = "hit";
const char BOOP[]  = "boop";
const char PEW[]   = "pew";


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

const UCHAR SHIP_UP      = VK_UP;
const UCHAR SHIP_DOWN    = VK_DOWN;
const UCHAR SHIP_LEFT    = VK_LEFT;
const UCHAR SHIP_RIGHT   = VK_RIGHT;
const UCHAR SHIP_SHOOT   = VK_SPACE;




#endif
