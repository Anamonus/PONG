#include "AIE.h"
#include <iostream>
#include <stdlibe.h>
#include <ctime>


int getRandomNumber(int high, int low)
{
	return rand() % high + low;
}
enum GAMESTATES
{
	MENU,
	GAMEPLAY,
	INSTRUCTIONS,
};
struct Player
{
	unsigned int spriteId;
	float width;
	float height;
	void setSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}
	float x;
	float y;
	void setPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	unsigned int moveUpKey;
	unsigned int moveDownKey;
	void setMovementKeys(unsigned int a_moveUpKey, unsigned int a_moveDownKey)
	{
		moveDownKey = a_moveDownKey;
		moveUpKey = a_moveUpKey;
	}
	unsigned int upExtreme;
	unsigned int downExtreme;
	void setExtremes(float a_upExtreme, float a_downExtreme)
	{
		upExtreme = a_upExtreme;
		downExtreme = a_downExtreme;
	}
	void Move(float a_fTimeStep, float a_fSpeed)
	{
		if (IsKeyDown(moveDownKey))
		{
			y -= a_fTimeStep * a_fSpeed;
			if (y < (downExtreme))
			{
				x = downExtreme;
			}
		}
		if (IsKeyDown(moveUpKey))
		{
			y += a_fTimeStep * a_fSpeed;
			if (y >(upExtreme))
			{
				y = (upExtreme);
			}
		}
		MoveSprite(spriteId, x, y);
	}
};
Player playerOne;
srand(time(NULL));
int screenWidth = 800;
int screenHeight = 600;
GAMESTATES eCurrentState = MENU;
int main( int argc, char* argv[] )
{	
    Initialise(screenWidth, screenHeight, false, "PONG");

	//playerOne already declared globally for the case of applying the reasoning for struct Ball
	playerOne.width = 64.f;
	playerOne.height = 10.f;
	playerOne.spriteId = CreateSprite("./images/Pong_player_1.png", playerOne.width, playerOne.height, true);
	playerOne.setMovementKeys('W', 'S');
	playerOne.x = screenWidth * 0.25f;
	playerOne.y = screenHeight * 0.5f;
	playerOne.setPosition(playerOne.x, playerOne.y);

	struct Ball
	{
		unsigned int dx
		unsigned int dy
		unsigned int spriteId;
		float width;
		float height;
		void setSize(float a_width, float a_height)
		{
			width = a_width;
			height = a_height;
		}
		unsigned int x;
		unsigned int y;
		void setPosition(float a_x, float a_y)
		{
			x = a_x;
			y = a_y;
		}
		
		bool setDirection()
		{
			
		}

	};

	Ball ball;
    SetBackgroundColour(SColour(0, 0, 0, 255));

    //Game Loop
    do
    {
		float fDeltaT = GetDeltaTime();

        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
