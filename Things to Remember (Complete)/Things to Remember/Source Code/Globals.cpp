#include "Globals.h"

void DrawAlphaSurface(int x, int y, SDL_Surface *source, SDL_Surface *destination, int alpha, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_SetAlpha(source, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
	SDL_BlitSurface(source,clip,destination,&offset);
}

void DrawSurface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source,clip,destination,&offset);
}

SDL_Surface *load_image(string file)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *fixedImage  = NULL;

	loadedImage = IMG_Load(file.c_str());

	if(loadedImage != NULL)
	{
		fixedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	if(fixedImage != NULL)
	{
		SDL_SetColorKey(fixedImage,SDL_SRCCOLORKEY,SDL_MapRGB(fixedImage->format,0,0xFF,0xFF));
	}

	return fixedImage;
}

TTF_Font    *font         = NULL;

SDL_Event event;

SDL_Rect gameCamera = {0,0,SCREEN_W,SCREEN_H};

SDL_Surface *mainScreen = NULL;

SDL_Rect tileClips[TILE_TYPES];

void ClipSpriteSheet(SDL_Rect clipsRight[], SDL_Rect clipsLeft[])
{

		  clipsRight[ 0 ].x = 0;
		  clipsRight[ 0 ].y = 0;
    	  clipsRight[ 0 ].w = PLAYER_W;
		  clipsRight[ 0 ].h = PLAYER_H;
		  
		  clipsRight[ 1 ].x = PLAYER_W;
		  clipsRight[ 1 ].y = 0;
		  clipsRight[ 1 ].w = PLAYER_W;
		  clipsRight[ 1 ].h = PLAYER_H;
		  
		  clipsRight[ 2 ].x = PLAYER_W * 2;
		  clipsRight[ 2 ].y = 0;
		  clipsRight[ 2 ].w = PLAYER_W;
		  clipsRight[ 2 ].h = PLAYER_H;
		  
		  clipsRight[ 3 ].x = PLAYER_W * 3;
		  clipsRight[ 3 ].y = 0;
		  clipsRight[ 3 ].w = PLAYER_W;
		  clipsRight[ 3 ].h = PLAYER_H;
		  
		  clipsRight[ 4 ].x = PLAYER_W * 4;
		  clipsRight[ 4 ].y = 0;
		  clipsRight[ 4 ].w = PLAYER_W;
		  clipsRight[ 4 ].h = PLAYER_H;
		  
		  clipsLeft[ 4 ].x = 0;
		  clipsLeft[ 4 ].y = PLAYER_H;
		  clipsLeft[ 4 ].w = PLAYER_W;
		  clipsLeft[ 4 ].h = PLAYER_H;
		  
		  clipsLeft[ 3 ].x = PLAYER_W;
		  clipsLeft[ 3 ].y = PLAYER_H;
		  clipsLeft[ 3 ].w = PLAYER_W;
		  clipsLeft[ 3 ].h = PLAYER_H;
		  
		  clipsLeft[ 2 ].x = PLAYER_W * 2;
		  clipsLeft[ 2 ].y = PLAYER_H;
		  clipsLeft[ 2 ].w = PLAYER_W;
		  clipsLeft[ 2 ].h = PLAYER_H; 
		  
		  clipsLeft[ 1 ].x = PLAYER_W * 3;
		  clipsLeft[ 1 ].y = PLAYER_H;
		  clipsLeft[ 1 ].w = PLAYER_W;
		  clipsLeft[ 1 ].h = PLAYER_H;
		  
		  clipsLeft[ 0 ].x = PLAYER_W * 4;
		  clipsLeft[ 0 ].y = PLAYER_H;
		  clipsLeft[ 0 ].w = PLAYER_W;
		  clipsLeft[ 0 ].h = PLAYER_H;

}

void CreateTileClips(SDL_Rect *TileClips)
{
			TileClips[TILE_BLANK].x = 0;
			TileClips[TILE_BLANK].y = 0;
			TileClips[TILE_BLANK].w = TILE_W;
			TileClips[TILE_BLANK].h = TILE_H;

			TileClips[TILE_LIGHTBLUE].x = TILE_W;
			TileClips[TILE_LIGHTBLUE].y = 0;
			TileClips[TILE_LIGHTBLUE].w = TILE_W;
			TileClips[TILE_LIGHTBLUE].h = TILE_H;

			TileClips[TILE_ORANGE].x = TILE_W * 2;
			TileClips[TILE_ORANGE].y = 0;
			TileClips[TILE_ORANGE].w = TILE_W;
			TileClips[TILE_ORANGE].h = TILE_H;

			TileClips[TILE_GREEN].x = 0;
			TileClips[TILE_GREEN].y = TILE_H;
			TileClips[TILE_GREEN].w = TILE_W;
			TileClips[TILE_GREEN].h = TILE_H;

			TileClips[TILE_INVISIBLE].x = 0;
			TileClips[TILE_INVISIBLE].y = 0;
			TileClips[TILE_INVISIBLE].w = TILE_W;
			TileClips[TILE_INVISIBLE].h = TILE_H;

			TileClips[TILE_DARKBLUE].x = TILE_W * 2;
			TileClips[TILE_DARKBLUE].y = TILE_H;
			TileClips[TILE_DARKBLUE].w = TILE_W;
			TileClips[TILE_DARKBLUE].h = TILE_H;

			TileClips[TILE_RED].x = 0;
			TileClips[TILE_RED].y = TILE_H * 2;
			TileClips[TILE_RED].w = TILE_W;
			TileClips[TILE_RED].h = TILE_H;

			TileClips[TILE_FAKE].x = TILE_W * 2;
			TileClips[TILE_FAKE].y = TILE_H;
			TileClips[TILE_FAKE].w = TILE_W;
			TileClips[TILE_FAKE].h = TILE_H;

			TileClips[TILE_PURPLE].x = TILE_W * 2;
			TileClips[TILE_PURPLE].y = TILE_H * 2;
			TileClips[TILE_PURPLE].w = TILE_W;
			TileClips[TILE_PURPLE].h = TILE_H;
}

bool CollisionTest(SDL_Rect A, SDL_Rect B)
{   
	int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    
    return true;
}

bool MARCollisionTest(int mouseX, int mouseY, SDL_Rect B)
{
	if( (mouseX > B.x) && (mouseX < B.x + B.w) && (mouseY > B.y) && (mouseY < B.y + B.h) ) // if mouse is inside of box
	{
		return true;
	}

	return false;
}

void CreateParticleClips(SDL_Rect clips[])
{
	clips[PARTICLE_RED].x = 0;
	clips[PARTICLE_RED].y = 0;
	clips[PARTICLE_RED].w = PARTICLE_W;
	clips[PARTICLE_RED].h = PARTICLE_H;

	clips[PARTICLE_DARKRED].x = PARTICLE_W;
	clips[PARTICLE_DARKRED].y = 0;
	clips[PARTICLE_DARKRED].w = PARTICLE_W;
	clips[PARTICLE_DARKRED].h = PARTICLE_H;

	clips[PARTICLE_BROWN].x = PARTICLE_W * 2;
	clips[PARTICLE_BROWN].y = 0;
	clips[PARTICLE_BROWN].w = PARTICLE_W;
	clips[PARTICLE_BROWN].h = PARTICLE_H;

	clips[PARTICLE_BLUE].x = 0;
	clips[PARTICLE_BLUE].y = PARTICLE_H;
	clips[PARTICLE_BLUE].w = PARTICLE_W;
	clips[PARTICLE_BLUE].h = PARTICLE_H;

	clips[PARTICLE_DARKBLUE].x = PARTICLE_W;
	clips[PARTICLE_DARKBLUE].y = PARTICLE_H;
	clips[PARTICLE_DARKBLUE].w = PARTICLE_W;
	clips[PARTICLE_DARKBLUE].h = PARTICLE_H;

	clips[PARTICLE_LIGHTBLUE].x = PARTICLE_W * 2;
	clips[PARTICLE_LIGHTBLUE].y = PARTICLE_H;
	clips[PARTICLE_LIGHTBLUE].w = PARTICLE_W;
	clips[PARTICLE_LIGHTBLUE].h = PARTICLE_H;

	clips[PARTICLE_YELLOW].x = 0;
	clips[PARTICLE_YELLOW].y = PARTICLE_H * 2;
	clips[PARTICLE_YELLOW].w = PARTICLE_W;
	clips[PARTICLE_YELLOW].h = PARTICLE_H;

	clips[PARTICLE_GREEN].x = PARTICLE_W;
	clips[PARTICLE_GREEN].y = PARTICLE_H * 2;
	clips[PARTICLE_GREEN].w = PARTICLE_W;
	clips[PARTICLE_GREEN].h = PARTICLE_H;

	clips[PARTICLE_WHITE].x = PARTICLE_W * 2;
	clips[PARTICLE_WHITE].y = PARTICLE_H * 2;
	clips[PARTICLE_WHITE].w = PARTICLE_W;
	clips[PARTICLE_WHITE].h = PARTICLE_H;
}
