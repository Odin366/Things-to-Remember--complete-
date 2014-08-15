#ifndef _CLEVEL_H
#define _CLEVEL_H

#include "Globals.h"


class Level
{
private:

	SDL_Surface *bgImage;
	SDL_Surface *fader;

	SDL_Surface *message;

	SDL_Color textColor;

	Tile *mapTiles[TILES_ACROSS][TILES_DOWN];
	Tile *lv5Tiles[LV_5_ACROSS][LV_5_DOWN];

	Button *button;

	void LayTiles(string map); // called by ctor, shouldn't be called otherwise

	int StartX;
	int StartY;

	bool msgFadedIn;
	bool msgFadedOut;

	bool msgFadeInBegun;
	bool msgFadeOutBegun;

	bool fadedIn;
	bool fadedOut;

	bool fadeInBegun; // is it fading or not fading
	bool fadeOutBegun; 

	int alpha; // for fader
	int msgAlpha;

	bool done;

	int msgX;
	int msgY;

	int width;
	int height;

	int id;

public:
	Level(string mapFileName, string bgImageName, int newID); 
	Level(string mapFileName, int id);
	~Level();

	void Draw(SDL_Rect *TileClips,SDL_Surface *tileSheet);
	void Update();
	void Handle_Events(SDL_Event event);

	void Finalize();

	void FadeIn(int speed);
	void FadeOut(int speed);

	void FadeMsgIn(int speed, int x, int y);
	void FadeMsgOut(int speed, int x, int y);

	void Load_Map(string mapFileName);

	Button *GetButton()
	{
		return button;
	}

	bool HasFadedIn()
	{
		return fadedIn;
	}

	bool HasFadedOut()
	{
		return fadedOut;
	}

	bool MsgFadedIn()
	{
		return msgFadedIn;
	}

	bool MsgFadedOut()
	{
		return msgFadedOut;
	}

	bool FadeOutBegun()
	{
		return fadeOutBegun;
	}

	bool FadeInBegun()
	{
		return fadeInBegun;
	}

	bool MsgFadeOutBegun()
	{
		return fadeOutBegun;
	}

	bool MsgFadeInBegun()
	{
		return msgFadeInBegun;
	}

	void Finish()
	{
		done = true;
	}

	bool ColAtXY(int x, int y)
	{
		if((id != 5) && ( x >= 0) && (x < TILES_ACROSS) && (y >= 0) && (y < TILES_DOWN)) // multi screen level
		{
			return mapTiles[x][y]->IsSolid();
		}
		else if((id == 5) && ( x >= 0) && (x < LV_5_ACROSS) && (y >= 0) && (y < LV_5_DOWN))
		{
			return lv5Tiles[x][y]->IsSolid();
		}
			
		return false;
	}

	SDL_Surface *GetMsg()
	{
		return message;
	}

	int GetStartX()
	{
		return StartX;
	}

	int GetStartY()
	{
		return StartY;
	}

	void End()
	{
		done = true;
	}

	void SetMessage(string msg)
	{
		message = TTF_RenderText_Solid(font,msg.c_str(),textColor);
	}

	bool isFinished()
	{
		return done;
	}

	int GetTileID(int x, int y)
	{
		if(id != 5)
		{
			return mapTiles[x][y]->GetID();
		}
		else if(id == 5)
		{
			return lv5Tiles[x][y]->GetID();
		}

		return false;
	}

	void SetWidth(int a)
	{
		width = a;
	}

	void SetHeight(int a)
	{
		height = a;
	}
	
	int GetID()
	{
		return id;
	}

	void SetID(int a)
	{
		id = a;
	}

	int GetWidth()
	{
		return width;
	}

	int GetHeight()
	{
		return height;
	}

	int GetMsgX()
	{
		return msgX;
	}

	int GetMsgY()
	{
		return msgY;
	}

	void SetMsgX(int a)
	{
		msgX = a;
	}

	void SetMsgY(int a)
	{
		msgY = a;
	}

	void BeginMsgFadeIn(int mx, int my)
	{
		if(msgFadeInBegun == false)
		{
			msgX = mx;
			msgY = my;
			msgAlpha       = 0;
			msgFadeInBegun = true;
		}
	}

	void BeginMsgFadeOut()
	{
		if(msgFadeOutBegun == false)
		{
			msgAlpha    = 255;
			msgFadeOutBegun = true;
		}
	}

	void BeginFadeIn()
	{
		if(fadeInBegun == false)
		{
			alpha       = 255;
			fadeInBegun = true;
		}
	}

	void BeginFadeOut()
	{
		if(fadeOutBegun == false)
		{
			alpha    = 0;
			fadeOutBegun = true;
		}
	}

	void ResetFades()
	{
		alpha = 0;
		msgAlpha = 0;

		msgFadedIn  = false;
		msgFadedOut = false;

		msgFadeInBegun  = false;
		msgFadeOutBegun = false;

		fadedIn  = false;
		fadedOut = false;

		fadeInBegun  = false;
		fadeOutBegun = false;
	}

	void ClearBackground(Uint32 color)
	{
		SDL_FillRect(mainScreen,&mainScreen->clip_rect,color);
	}
};

#endif