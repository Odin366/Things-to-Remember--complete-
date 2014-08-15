#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

enum ButtonTypes
{
	IMAGE = 1,  // button used the constructor with an image
	TEXT  = 2  // button used the constructor with text
};

class Button
{
private:

	TTF_Font *buttonFont;

	SDL_Surface *content;

	SDL_Rect collisionBox;

	int buttonType;

	SDL_Color bgClr; // background color
	SDL_Color fgClr; // foreground color
	SDL_Color borderClr; // border color
	SDL_Color hoverClr; //hover color

	//event variables
	bool leftClicked;  // mouse left clicked button
	bool rightClicked; // mouse right clicked button
	bool mousedOver;   // mouse is hovering over button
	bool mouseClicked;   // is the mouse over the button when clicked

public:

	Button(int x, int y, SDL_Surface *image); // button uses an image


	Button(int x, int y, string text, int fontSize); //use default colors
	Button(int x, int y, string text, int fontSize, SDL_Color textColor, SDL_Color fillColor, SDL_Color borderColor, SDL_Color hoverColor);

	~Button();

	void Draw();		 // switch(buttonType)
	void HandleEvents(SDL_Event event); // on click, rollover, release,
	void Update(); 

	bool wasLeftClicked()
	{
		return leftClicked;
	}

	bool wasRightClicked()
	{
		return rightClicked;
	}

	bool isMousedOver()
	{
		return mousedOver;
	}

	SDL_Rect GetCollisionBox()
	{
		return collisionBox;
	}

	void SetX(int x)
	{
		collisionBox.x = x;
	}

	void SetY(int y)
	{
		collisionBox.y = y;
	}

};

