#include "Globals.h"

Button::Button(int x, int y, SDL_Surface *image)
{
	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = image->w;
	collisionBox.h = image->h;

	buttonType = IMAGE;

	leftClicked  = false;
	rightClicked = false;
	mousedOver   = false;
	
	hoverClr.r = 72;
	hoverClr.g = 61;
	hoverClr.b = 139;
}

Button::Button(int x, int y, string text, int fontSize)
{
	buttonFont = TTF_OpenFont("dnealiancursive.ttf", fontSize);

	fgClr.r = 255;
	fgClr.g = 255;
	fgClr.b = 255; // green text

	bgClr.r = 0;
	bgClr.g = 0;
	bgClr.b = 255; // 

	borderClr.r = 255;
	borderClr.g = 0;
	borderClr.b = 0; // red border
		
	hoverClr.r = 72;
	hoverClr.g = 61;
	hoverClr.b = 139;

	content = TTF_RenderText_Solid(buttonFont,text.c_str(),fgClr);

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = content->w;
	collisionBox.h = content->h;

	buttonType = TEXT;

	leftClicked  = false;
	rightClicked = false;
	mousedOver   = false;
}

Button::Button(int x, int y, string text, int fontSize, SDL_Color textColor, SDL_Color fillColor, SDL_Color borderColor, SDL_Color hoverColor)
{
	buttonFont = TTF_OpenFont("dnealiancursive.ttf", fontSize);

	fgClr = textColor;
	bgClr = fillColor;
	borderClr = borderColor;
	hoverClr = hoverColor;

	content = TTF_RenderText_Solid(buttonFont,text.c_str(),fgClr);

	collisionBox.x = x;
	collisionBox.y = y;
	collisionBox.w = content->w;
	collisionBox.h = content->h;

	buttonType = TEXT;

	leftClicked   = false;
	rightClicked  = false;
	mousedOver    = false;


}

Button::~Button()
{
	TTF_CloseFont(buttonFont);
	SDL_FreeSurface(content);
}

void Button::Draw()
{
	if(buttonType == IMAGE)
	{
		DrawSurface(collisionBox.x, collisionBox.y, content, mainScreen);
	}
	else if(buttonType == TEXT)
	{
		if(!mousedOver)
		{
			SDL_FillRect(mainScreen, &collisionBox, SDL_MapRGB(mainScreen->format, bgClr.r, bgClr.g, bgClr.b));
			DrawSurface(collisionBox.x, collisionBox.y, content, mainScreen);
			rectangleRGBA(mainScreen, collisionBox.x  , collisionBox.y, collisionBox.x + collisionBox.w, collisionBox.y + collisionBox.h, borderClr.r, borderClr.g, borderClr.b, 255);
		}
		else if(mousedOver)
		{
			SDL_FillRect(mainScreen, &collisionBox, SDL_MapRGB(mainScreen->format, hoverClr.r, hoverClr.g, hoverClr.b));
			DrawSurface(collisionBox.x  , collisionBox.y, content, mainScreen);
			rectangleRGBA(mainScreen, collisionBox.x, collisionBox.y, collisionBox.x + collisionBox.w, collisionBox.y + collisionBox.h, borderClr.r, borderClr.g, borderClr.b, 255);
		}
	}
}

void Button::HandleEvents(SDL_Event event)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);

	if(event.type == SDL_MOUSEMOTION)
	{
		x = event.motion.x;
		y = event.motion.y;

		if(MARCollisionTest(x, y, collisionBox))
		{
			mousedOver = true;
		}
		else
		{
			mousedOver = false;
		}

	}
	else if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch(event.button.button)
		{
		case SDL_BUTTON_LEFT:

			if(MARCollisionTest(x, y, collisionBox))
			{
				leftClicked = true;	// if the mouse clicks and is over the button, register it
			}

			break;

		case SDL_BUTTON_RIGHT:

			if(MARCollisionTest(x, y, collisionBox))
			{
				rightClicked = true;
			}

			break;
		}
	}
	else if(event.type == SDL_MOUSEBUTTONUP)
	{
		switch(event.button.button)
		{
		case SDL_BUTTON_LEFT:

			if(MARCollisionTest(x, y, collisionBox))
			{
				leftClicked  = false;  // if the mouse lets go over the button and started the click over the button
			}

			break;

		case SDL_BUTTON_RIGHT:

			if(MARCollisionTest(x, y, collisionBox))
			{
				rightClicked = false;
			}

			break;
		}
	}
}

void Button::Update()
{
}