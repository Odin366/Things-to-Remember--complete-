#ifndef GLOBALS_H
#define GLOBALS_H

#define PI 3.1415

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_gfx.h"
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "Debug.h"
#include "CTile.h"
#include "CButton.h"
#include "CParticleSys.h"

	using namespace std;

	const int FADE_SPEED     = 10;
	const int MSG_FADE_SPEED = 4;

	const int MAX_FPS    = 24;

	// Player Attributes

	const int PLAYER_W  = 32;
	const int PLAYER_H  = 32;

	const int SCREEN_W   = 640;
	const int SCREEN_H	 = 480;
	const int SCREEN_BPP = 32;

	const int TILE_W = 32;
	const int TILE_H = 32;

	const int TILE_TYPES   = 9;

	const int TILES_ACROSS = 20;
	const int TILES_DOWN   = 15;

	const int LV_5_ACROSS = 80;
	const int LV_5_DOWN   = 15;

	const int LV_5_WIDTH  = 640*4;
	const int LV_5_HEIGHT = 480;

	//button state defintions
	const int LEFT_BUTTON   = 1;
	const int MIDDLE_BUTTON = 2;
	const int RIGHT_BUTTON  = 3;
	extern SDL_Surface *mainScreen;

	const int GRAVITY = 4;

	extern SDL_Event event;

	enum  // particles
	{
		PARTICLE_RED	   = 0,
		PARTICLE_DARKRED   = 1,
		PARTICLE_BROWN	   = 2,
		PARTICLE_BLUE	   = 3,
		PARTICLE_DARKBLUE  = 4,
		PARTICLE_LIGHTBLUE = 5,
		PARTICLE_YELLOW	   = 6,
		PARTICLE_GREEN     = 7,
		PARTICLE_WHITE     = 8
	};

	enum // Temp tile types
	{
		TILE_BLANK	   = 0,
		TILE_LIGHTBLUE = 1,
		TILE_ORANGE    = 2,
		TILE_GREEN     = 3,
		TILE_INVISIBLE = 4,
		TILE_DARKBLUE  = 5,
		TILE_RED       = 6,
		TILE_FAKE      = 7,
		TILE_PURPLE    = 8,
		TILE_STARTPOS  = 9
	};

	const int LOWTILEBOUND  = TILE_BLANK;
	const int HIGHTILEBOUND = TILE_STARTPOS;

	enum // Directions
	{
		RIGHT = 0,
		LEFT  = 1,
		UP    = 2,
		DOWN  = 3
	};


	enum // particle systems
	{
		NONE      = 0,
		STARFIELD = 1,
		SNOW	  = 2
	};
		
	extern void DrawAlphaSurface(int x, int y, SDL_Surface *source, SDL_Surface *destination, int alpha, SDL_Rect *clip = NULL);
	extern void DrawSurface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL);
	extern bool CollisionTest(SDL_Rect A, SDL_Rect B);
	extern bool MARCollisionTest(int mouseX, int mouseY, SDL_Rect B); //mouse and rect

	extern SDL_Surface *load_image(string file);

	extern TTF_Font    *font;
	extern SDL_Color textcolor; 

	extern SDL_Rect gameCamera;

	extern void CreateParticleClips(SDL_Rect clips[]);

	// for Tile image clipping
	extern SDL_Rect tileClips[TILE_TYPES];
	
	// general function for clipping spritesheets with 5 frames and two directions
	extern void ClipSpriteSheet(SDL_Rect clipsRight[], SDL_Rect clipsLeft[]);
	extern void CreateTileClips(SDL_Rect *TileClips);



#endif