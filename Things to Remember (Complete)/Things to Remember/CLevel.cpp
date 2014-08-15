#include "CLevel.h"
#include "CTile.h"

Level::Level(string mapFileName, string bgImageName, int newID)
{
	id = newID;

	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	button = NULL;

	if(id == 7)
	{
		button = new Button(SCREEN_W - 5*TILE_W, SCREEN_H - 3*TILE_H,"Again?",28);
	}

	if(id != 5)
	{
		width  = 640;
		height = 480;
	}
	else if(id == 5)
	{
		width  = LV_5_WIDTH;
		height = LV_5_HEIGHT;
	}

	done = false;

	ResetFades();

	fader   = load_image("fader.png");
	bgImage = NULL;
	bgImage = load_image(bgImageName.c_str());
	this->LayTiles(mapFileName);

	msgX = 0;
	msgY = 0;
}

Level::Level(string mapFileName, int newID)
{
	id = newID;

	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;

	done = false;

	button = NULL;

	if(id != 5)
	{
		width  = 640;
		height = 480;
	}
	else if(id == 5)
	{
		width  = LV_5_WIDTH;
		height = LV_5_HEIGHT;
	}

	msgX = 0;
	msgY = 0;

	ResetFades();

	fader   = load_image("fader.png");
	bgImage = NULL;
	this->LayTiles(mapFileName);
}


Level::~Level()
{

}

void Level::LayTiles(string map)
{
	Debug *dbg = Debug::GetInstance();

	ifstream mapFile;
	mapFile.open(map.c_str(),ios::in);
	if(mapFile.fail())
	{
		dbg->Print("Cannot open map, map file probably doesn't exist");
	}

	int x    = 0;
	int y    = 0;
	int type = -1;

	if(id != 5)
	{
		for(int i = 0; i < TILES_DOWN; i++)
		{
			for(int j = 0; j < TILES_ACROSS; j++)
			{
				mapFile >> type;

				if(mapFile.fail())
				{
					dbg->Print("Map File failed to be read");
					break;
				}

				if((type >= LOWTILEBOUND) && (type <= HIGHTILEBOUND))
				{
					if(type == TILE_STARTPOS)
					{
						mapTiles[j][i] = new Tile(x,y,TILE_BLANK);

						StartX = mapTiles[j][i]->GetCollisionBox().x;
						StartY = mapTiles[j][i]->GetCollisionBox().y;
					}
					else
					{
						mapTiles[j][i] = new Tile(x,y,type);
					}
				}

					x += TILE_W;
					
					if(x >= width)
					{
						x = 0;
						y += TILE_H;
					}
			}
		}

		mapFile.close();
	}
	else if(id == 5)
	{
		for(int i = 0; i < LV_5_DOWN; i++)
		{
			for(int j = 0; j < LV_5_ACROSS; j++)
			{
				mapFile >> type;

				if(mapFile.fail())
				{
					dbg->Print("Map File failed to be read");
					break;
				}

				if((type >= LOWTILEBOUND) && (type <= HIGHTILEBOUND))
				{
					if(type == TILE_STARTPOS)
					{
						lv5Tiles[j][i] = new Tile(x,y,TILE_BLANK);

						StartX = lv5Tiles[j][i]->GetCollisionBox().x;
						StartY = lv5Tiles[j][i]->GetCollisionBox().y;
					}
					else
					{
						lv5Tiles[j][i] = new Tile(x,y,type);
					}
				}

					x += TILE_W;
					
					if(x >= width)
					{
						x = 0;
						y += TILE_H;
					}
			}
		}

		mapFile.close();
	}

}

void Level::Draw(SDL_Rect *TileClips,SDL_Surface *tileSheet)
{
	ClearBackground(SDL_MapRGB(mainScreen->format,0,0,0));

	if((bgImage != NULL) && (id == 7))
	{
		DrawSurface(TILE_W - 9, -9, bgImage, mainScreen);

		boxRGBA(mainScreen, 0, SCREEN_H - 2*TILE_H, SCREEN_W, SCREEN_H - TILE_H, 0, 0, 0, 255); // prevents border from showing on image
	}

	if((bgImage != NULL) && (id != 7))
	{
		DrawSurface(0,0,bgImage,mainScreen);
	}

	if( id != 5)
	{
		for(int i = 0; i < TILES_DOWN; i++)
		{
			for(int j = 0; j < TILES_ACROSS; j++)
			{
				mapTiles[j][i]->Display(TileClips,tileSheet);
			}
		}
	}
	else if( id == 5 )
	{
		for(int i = 0; i < LV_5_DOWN; i++)
		{
			for(int j = 0; j < LV_5_ACROSS; j++)
			{
				lv5Tiles[j][i]->Display(TileClips, tileSheet);
			}
		}
	}

	if(button != NULL)
	{
		button->Draw();
	}
}

void Level::Update()
{
	if(button != NULL)
	{
		button->Update();
	}
}

void Level::Handle_Events(SDL_Event event)
{
	if(button != NULL)
	{
		button->HandleEvents(event);
	}
}

void Level::Finalize()
{
	if( id != 5)
	{
		for(int i = 0; i < TILES_DOWN; i++)
		{
			for(int j = 0; j < TILES_ACROSS; j++)
			{
				delete mapTiles[j][i];
			}
		}
	}
	else if( id == 5 )
	{
		for(int i = 0; i < LV_5_DOWN; i++)
		{
			for(int j = 0; j < LV_5_ACROSS; j++)
			{
				delete lv5Tiles[j][i];
			}
		}
	}

	if(bgImage != NULL)
	{
		SDL_FreeSurface(bgImage);
	}

	SDL_FreeSurface(fader);
	
	if(message != NULL)
	{
		SDL_FreeSurface(message);
	}

	if(button != NULL)
	{
		delete button;
	}
}

void Level::FadeIn(int speed)
{ 
	BeginFadeIn();

	if(alpha > 0)
	{
		DrawAlphaSurface(0, 0, fader, mainScreen, alpha);

		alpha -= speed;

		if(alpha < 0)
		{
			alpha = 0;
		}
	}
	else
	{
		DrawAlphaSurface(0, 0, fader, mainScreen, alpha);  // prevents blinking during transition from reaching desired transparency to blitting afterward
		fadedIn = true;
	}

}

void Level::FadeOut(int speed)
{ 
	BeginFadeOut();

	if(alpha < 255)
	{
		DrawAlphaSurface(0, 0, fader, mainScreen, alpha);

		alpha += speed;

		if(alpha > 255)
		{
			alpha = 255;
		}
	}
	else
	{
		DrawAlphaSurface(0, 0, fader, mainScreen, alpha);
		fadedOut = true;
	}
}

void Level::FadeMsgIn(int speed, int x, int y)
{

	BeginMsgFadeIn(x,y);

	if(msgAlpha < 255)
	{
		DrawAlphaSurface(x, y, message, mainScreen, msgAlpha);

		msgAlpha += speed;

		if(msgAlpha > 255)
		{
			msgAlpha = 255;
		}
	}
	else
	{
		DrawAlphaSurface(x, y, message, mainScreen, msgAlpha);
		msgFadedIn = true;
	}
}

void Level::FadeMsgOut(int speed, int x, int y)
{
	BeginMsgFadeOut();

	msgX = x;
	msgY = y;

	if(msgAlpha > 0)
	{
		DrawAlphaSurface(x, y, message, mainScreen, msgAlpha);

		msgAlpha -= speed;

		if(msgAlpha < 0)
		{
			msgAlpha = 0;
		}
	}
	else
	{
		DrawAlphaSurface(x, y, message, mainScreen, msgAlpha);
		msgFadedOut = true;
	}
}
