#include "CPlayer.h"
#include "CObject.h"

#define SIDEVEL 20 // horizontal velocity
#define JUMPVEL 32 // jump velocity

Player::Player(Level *level)
{
	startX	   = level->GetStartX();
	startY	   = level->GetStartY();
	collisionBox.x = startX;
	collisionBox.y = startY;
	collisionBox.h = PLAYER_H;
	collisionBox.w = PLAYER_W;

	keys = SDL_GetKeyState(NULL);
	
	frame = 1;

	dir	= 0;

	xVel = 0;
	yVel = 0;

	falling = false;
	jumping = false;

	dead    = false;

	showBox = false;

}

Player::~Player()
{
}

void Player::Draw(Level *level)
{
	if(!dead)
	{
		CenterCamera(level);

		if( xVel > 0)
		{
			dir = RIGHT;
			frame++;
		}
		else if( xVel < 0)
		{
			dir = LEFT;
			frame++;
		}
		
		if(frame == 5)
		{
			frame = 0;
		}

		if(xVel == 0)
		{
			frame = 0;
		}

		if( dir == LEFT)
		{
			boxRGBA(mainScreen,collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, (collisionBox.x + PLAYER_W) - gameCamera.x, (collisionBox.y + PLAYER_H) - gameCamera.y,0,0,255,255);

			if(showBox == true)
			{
				rectangleRGBA(mainScreen,collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, (collisionBox.x + PLAYER_W) - gameCamera.x, (collisionBox.y + PLAYER_H) - gameCamera.y,255,0,0,255);
			}
		}
		else if( dir == RIGHT)
		{
			boxRGBA(mainScreen,collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, (collisionBox.x + PLAYER_W) - gameCamera.x, (collisionBox.y + PLAYER_H) - gameCamera.y,0,0,255,255);
				
			if(showBox == true)
			{
				rectangleRGBA(mainScreen, collisionBox.x - gameCamera.x, collisionBox.y - gameCamera.y, (collisionBox.x + PLAYER_W) - gameCamera.x, (collisionBox.y + PLAYER_H) - gameCamera.y,255,0,0,255);
			}
		}
	}
}

void Player::Handle_Events(SDL_Event event, Level *level)
{
	if(!dead)
	{
		if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
			case SDLK_F2:
				ToggleBox();
				break;
			}
		}

		xVel = 0;
		
		if(keys[SDLK_RIGHT])
		{
			xVel = SIDEVEL;
		}

		if(keys[SDLK_LEFT])
		{
			xVel = -SIDEVEL;
		}

		if((level->GetID() != 3) && (level->GetID() != 4))
		{
			if(keys[SDLK_UP])
			{
				if(!jumping)
				{
					yVel = -JUMPVEL;
					jumping = true;
				}
			}
		}else if(level->GetID() == 4)
		{
			yVel = 0;

			if(keys[SDLK_UP])
			{
				yVel = -SIDEVEL; // Upward and downward velocities for flying level are the same
			}

			if(keys[SDLK_DOWN])
			{
				yVel = SIDEVEL;
			}
		}
	}
}

void Player::Update(Level *level)
{
	startX = level->GetStartX();
	startY = level->GetStartY();

	if( collisionBox.y > level->GetHeight() )
	{
		dead = true;
	}

	if(!dead)
	{
		int tileNum; // for checking collisions with tiles in the level

		if(xVel > 0) // if moving right
		{
			if(CollisionVer(collisionBox.x + collisionBox.w + xVel, collisionBox.y, tileNum, level))
			{
				collisionBox.x = (tileNum*TILE_W) - collisionBox.w - 1;
			}
			else
			{
				collisionBox.x += xVel;

				if(collisionBox.x > level->GetWidth() - PLAYER_W)
				{
					collisionBox.x = level->GetWidth() - PLAYER_W;
				}
			}
		}
		else if(xVel < 0)
		{
			
			if(CollisionVer(collisionBox.x + xVel, collisionBox.y, tileNum, level))
			{
				collisionBox.x = ((tileNum + 1)* TILE_W);
			}
			else
			{
				collisionBox.x += xVel;

				if(collisionBox.x < -1)
				{
					collisionBox.x = -1;
				}
			}
		}

		if(yVel < 0)
		{
			if(CollisionHor(collisionBox.x, collisionBox.y + yVel, tileNum, level))
			{
				collisionBox.y = (tileNum+1) * TILE_H + 1;
				yVel = 0;
			}
			else
			{
				collisionBox.y  += yVel;

				if((collisionBox.y < 0) && level->GetID() == 4)
				{
					collisionBox.y = 0;
				}
				
				if(level->GetID() != 4) // flying level
				{
					yVel += GRAVITY;
				}
			}
		}
		else // falling
		{
			if(CollisionHor(collisionBox.x, collisionBox.y + yVel + PLAYER_H, tileNum, level))
			{
				collisionBox.y = tileNum*TILE_H - collisionBox.h - 1;
				yVel = 1;

				if(level->GetID() != 4) // flying level
				{
					if(!keys[SDLK_UP])
					{
						jumping = false;
					}
				}
			}
			else 
			{
				collisionBox.y  += yVel;

				if(level->GetID() != 4) // flying level
				{
				yVel += GRAVITY;

					if(yVel > TILE_H)
					{
						yVel = TILE_H;
					}

					jumping = true;
				}
			}
		}
	}
	else if(dead)
	{
		Reset();
		Rez();
	}
}


void Player::ToggleBox()
{
	if(showBox == true)
	{
		showBox = false;
	}
	else if(showBox == false)
	{
		showBox = true;
	}
}

void Player::CenterCamera(Level *level)
{
	gameCamera.x = (collisionBox.x + PLAYER_W/2) - SCREEN_W/2;
	gameCamera.y = (collisionBox.y + PLAYER_H/2) - SCREEN_H/2;

	if(gameCamera.x < 0)
	{
		gameCamera.x = 0;
	}

	if(gameCamera.x > level->GetWidth() - gameCamera.w)
	{
		gameCamera.x = level->GetWidth() - gameCamera.w;
	}

	if(gameCamera.y < 0)
	{
		gameCamera.y = 0;
	}

	if(gameCamera.y > level->GetHeight() - gameCamera.h)
	{
		gameCamera.y = level->GetHeight() - gameCamera.h;
	}

}

bool Player::CollisionHor(int x, int y, int &tileY, Level *level)
{
	int tilePixX = x - (x %TILE_W );  // position of tile in pixels
	int stopWidth = x + PLAYER_W; 

	int tileX = tilePixX/TILE_W; // map coordinate
	tileY = y/TILE_H; // map coordinate
	

	while(tilePixX <= stopWidth)
	{
		if(level->ColAtXY(tileX, tileY))
		{
 			if((level->GetTileID(tileX, tileY) != TILE_GREEN) && (level->GetTileID(tileX, tileY) != TILE_RED) && (level->GetTileID(tileX, tileY) != TILE_FAKE) && (level->GetTileID(tileX, tileY) != TILE_PURPLE))
			{
				return true;
			}
			else if((level->GetTileID(tileX, tileY) == TILE_PURPLE))
			{
				if(level->GetID() != 7)
				{
					level->Finish();
					return true;
				}
				else if(level->GetID() == 7)
				{
					return true;
				}
			}

			return false;
			break;
		}

		tileX++;
		tilePixX += TILE_W;
	}

	return false;
}

bool Player::CollisionVer(int x, int y, int &tileX, Level *level)
{
	int tilePixY   = y - ( y % TILE_H );  // position of tile in pixels
	int stopHeight = y + PLAYER_H; 

	tileX = x/TILE_W; // map coordinate
	int tileY = tilePixY/TILE_H;// map coordinate
	

	while(tilePixY <= stopHeight)
	{
		if(level->ColAtXY(tileX, tileY))
		{
			if((level->GetTileID(tileX, tileY) != TILE_GREEN) && (level->GetTileID(tileX, tileY) != TILE_RED) && (level->GetTileID(tileX, tileY) != TILE_FAKE) && (level->GetTileID(tileX, tileY) != TILE_PURPLE))
			{
				return true;

			}else if((level->GetTileID(tileX, tileY) == TILE_PURPLE))
			{
				if(level->GetID() != 7)
				{
					level->Finish();
					return true;
				}
				else if(level->GetID() == 7)
				{
					return true;
				}
			}

			return false;
			break;
		}

		tileY++;
		tilePixY += TILE_H;
	}

	return false;
}