#include "AIE.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>   
#include <stdlib.h> 
#include <Windows.h>
#include <Windowsx.h>

using namespace std;
enum GAMESTATES
{
	MENU,
	GAMEPLAY,
	INSTRUCTIONS,
};

int screenWidth = 800;
int screenHeight = 600;
int speed = 500;
int scoreBlue = 0;
int scoreRed = 0;
//Player scores and display
char bufferRed[10] = "0";
char bufferBlue[10] = "0";
char blueHighscore[10];
char redHighscore[10];
char redLabel[14] = "Red Highscore";
char blueLabel[15] = "Blue Highscore";
char reaturnToMain[41] = "Press 'space' to return";
char quit[41] = "Press 'Q' to quit";
float ballSpeedX = 0.35;
float ballSpeedY = 0.35;
bool gameRunning = true;
int highScore;
double iMouseY;
double iMouseX;


struct Button
{
	float bX, bY, width, height;
	unsigned int spriteId;
	bool clicked = false;
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
		MoveSprite(spriteId, x, y);
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
				y = downExtreme;
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
struct Ball
{
	float dx = ballSpeedX;
	float dy = ballSpeedY;
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
	void moveX(float a_speed)
	{
		x += a_speed;
		MoveSprite(spriteId, x, y);
		DrawSprite(spriteId);
	}
	void moveY(float a_speed)
	{
		y += a_speed;
		MoveSprite(spriteId, x, y);
		DrawSprite(spriteId);
	}
};

//Declaration of structs
Ball ball;
Player playerOne;
Player playerTwo;
Button play;
Button instrct;
Button menu;



GAMESTATES eCurrentState = MENU;
int main(int argc, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "PONG");

	//Retrieving data from I/O's to display highscores
	fstream file;
	file.open("PlayerOneScore.txt", ios::in);
	int playerOneHighscore = 0;
	file >> playerOneHighscore;
	file.close();

	file.open("PlayerTwoScore.txt", ios::in);
	int playerTwoHighscore = 0;
	file >> playerTwoHighscore;
	file.close();

	//Properties for player one
	playerOne.width = 48.f;
	playerOne.height = 156.f;
	playerOne.spriteId = CreateSprite("./images/Pong_player_1.png", playerOne.width, playerOne.height, true);
	playerOne.setMovementKeys('W', 'S');
	playerOne.x = screenWidth * 0.15f;
	playerOne.y = screenHeight * 0.5f;
	playerOne.setPosition(playerOne.x, playerOne.y);
	playerOne.upExtreme = screenHeight - (playerOne.height*.5);
	playerOne.downExtreme = (playerOne.height*.5);

	//properties for player two
	playerTwo.width = 48.f;
	playerTwo.height = 156.f;
	playerTwo.spriteId = CreateSprite("./images/Pong_player_2.png", playerTwo.width, playerTwo.height, true);
	playerTwo.setMovementKeys('O', 'L');
	playerTwo.x = screenWidth * 0.85f;
	playerTwo.y = screenHeight * 0.5f;
	playerTwo.setPosition(playerTwo.x, playerTwo.y);
	playerTwo.upExtreme = screenHeight - (playerTwo.height*.5);
	playerTwo.downExtreme = (playerTwo.height*.5);

	//properties for button with text PLAY
	play.bX = screenWidth * 0.33;
	play.bY = screenHeight * 0.25;
	play.width = 250;
	play.height = 125;
	play.clicked = false;
	play.spriteId = CreateSprite("./images/pong_play_button.png", play.width, play.height, true);
	MoveSprite(play.spriteId, play.bX, play.bY);

	//proerties for menu button
	//ALL OMMITTED EXCEPT ONE BECAUSE I'M LAZY
//	menu.bX = screenWidth * .80;
//	menu.bY = screenHeight * .75;
//	menu.height = 125;
//	menu.width = 250;
	menu.clicked = false;
//	menu.spriteId = CreateSprite("./images/pong_menu_button.png", menu.width, menu.height, true);
	//MoveSprite(menu.spriteId, menu.bX, menu.bY);

	//properties for instructions button
	instrct.bX = screenWidth * .67;
	instrct.bY = screenHeight * .25;
	instrct.width = 250;
	instrct.height = 125;
	instrct.clicked - false;
	instrct.spriteId = CreateSprite("./images/pong_instructions_button.png", instrct.width, instrct.height, true);
	MoveSprite(instrct.spriteId, instrct.bX, instrct.bY);


	//properties for the Ball
	ball.x = (screenWidth / 2);
	ball.y = (screenHeight / 2);
	ball.width = 32;
	ball.height = 32;
	ball.spriteId = CreateSprite("./images/Pong_ball.png", ball.width, ball.height, true);
	MoveSprite(ball.spriteId, ball.x, ball.y);

	SetBackgroundColour(SColour(0, 0, 0, 255));
	//Preparing the menu backgrounds
	int instrctScreen = CreateSprite("./images/instructions_screen.png", screenWidth, screenHeight, true);
	int titeleScreen = CreateSprite("./images/title_screen.png", screenWidth, screenHeight, true);
	MoveSprite(titeleScreen, screenWidth / 2, screenHeight / 2);
	MoveSprite(instrctScreen, screenWidth / 2, screenHeight / 2);

	POINT mouse;

	//Game Loop
	do
	{
		float fDeltaT = GetDeltaTime();
		switch (eCurrentState)
		{
		case MENU:
			//Making sure the states return to false when cycling menus
			play.clicked = false;
			menu.clicked = false;
			instrct.clicked = false;
			//Tracking the mouse in order to tell if it is in contact with a button
			GetMouseLocation(iMouseX, iMouseY);
			DrawSprite(play.spriteId);
			DrawSprite(instrct.spriteId);
			DrawSprite(titeleScreen);
			itoa(playerOneHighscore, redHighscore, 10);
			itoa(playerTwoHighscore, blueHighscore, 10);
			DrawString(quit, screenWidth * .38, screenHeight / 2);
			ClearScreen();
			//Drawing Highscore and their lables
			DrawString(blueLabel, screenWidth * .03, screenHeight * .10);
			DrawString(redLabel, screenWidth * .76, screenHeight * .10);
			DrawString(blueHighscore, screenWidth * .15, screenHeight * .05);
			DrawString(redHighscore, screenWidth * .85, screenHeight * .05);
			//Since the mouse location draws differently I couldn't figure out how to detect via the button's Y position so I just used its location from the screen height
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && iMouseX > (instrct.bX - (instrct.height / 2)) && iMouseX < (instrct.bX + (instrct.height / 2))
				&& iMouseY >((screenHeight * .75) - (instrct.height / 2)) && iMouseY < ((screenHeight * .75) + (instrct.height / 2)))
			{
				instrct.clicked = true;
			}
			if (instrct.clicked)
			{
				eCurrentState = INSTRUCTIONS;
			}
			//Since the mouse location draws differently I couldn't figure out how to detect via the button's Y position so I just used its location from the screen height
			if (GetMouseButtonDown(MOUSE_BUTTON_1) && iMouseX > (play.bX - (play.height / 2)) && iMouseX < (play.bX + (play.height / 2))
				&& iMouseY >((screenHeight * .75) - (play.height / 2)) && iMouseY < ((screenHeight * .75) + (play.height / 2)))
			{
				play.clicked = true;
			}
			if (play.clicked)
			{
				eCurrentState = GAMEPLAY;
			}
			if (IsKeyDown('Q'))
			{
				gameRunning = false;
			}
			scoreBlue = 0;
			scoreRed = 0;
			break;
		case INSTRUCTIONS:
			play.clicked = false;
			menu.clicked = false;
			instrct.clicked = false;
			DrawSprite(instrctScreen);
			DrawString(reaturnToMain, screenWidth * .55, screenHeight * .85);
			ClearScreen();
			//The same code above wasn't working so I decided to be lazy and do this
			if (IsKeyDown(' '))
			{
				menu.clicked = true;
			}
			if (menu.clicked)
			{
				eCurrentState = MENU;
			}
			break;
		case GAMEPLAY:
			//swapped the itoa command to the top so when the game is replayed it shows the correct score
			play.clicked = false;
			menu.clicked = false;
			instrct.clicked = false;
			itoa(scoreBlue, bufferBlue, 10);
			itoa(scoreRed, bufferRed, 10);
			DrawString(bufferBlue, screenWidth * .85, screenHeight * .95);
			DrawString(bufferRed, screenWidth * .15, screenHeight * .95);
			ball.dx = ballSpeedX;
			ball.dy = ballSpeedY;
			ball.moveX(ball.dx);
			ball.moveY(ball.dy);
			// The mess below is my half assed attempt at creating collision detection within all sides of whatever is being touched
			if ((ball.x > screenWidth - (ball.width / 2)) || (ball.x < (ball.width / 2)) || ((playerOne.y > ball.y - playerOne.height / 2 && playerOne.y < ball.y + playerOne.height / 2) 
				&& (playerOne.x > ball.x - ((playerOne.width / 2) + ball.width / 2) && playerOne.x < ((ball.x + playerOne.width / 2) + ball.width / 2))))
			{
				if (ballSpeedX < 0)
				{
					ballSpeedX = (ballSpeedX * -1);
				}

			}
			if (ball.y > screenHeight - (ball.height / 2) || (ball.y < (ball.height / 2)))
			{
				ballSpeedY = (ballSpeedY * -1);
			}
			// Second verse same as the first
			if (((playerTwo.y > ball.y - playerTwo.height / 2 && playerTwo.y < ball.y + playerTwo.height / 2) && (playerTwo.x > ball.x - ((playerTwo.width / 2) + ball.width / 2) 
				&& playerTwo.x <((ball.x + playerTwo.width / 2) + ball.width / 2))))
			{
				if (ballSpeedX > 0)
				{
					ballSpeedX = (ballSpeedX * -1);
				}
			}
			//Logic for when the ball scores against red player
			if (ball.x > screenWidth - (ball.width / 2))
			{
				DestroySprite(ball.spriteId);
				scoreRed++;
				ballSpeedX = (ballSpeedX * -1);
				ball.x = screenWidth / 2;
				ball.y = screenHeight / 2;
				ball.spriteId = CreateSprite("./images/Pong_ball.png", ball.width, ball.height, true);
				
			}
			//Logic for when the ball scores against blue player
			if (ball.x < (ball.width / 2))
			{
				DestroySprite(ball.spriteId);
				scoreBlue++;
				ballSpeedY = (ballSpeedY * -1);
				ball.x = screenWidth / 2;
				ball.y = screenHeight / 2;
				ball.spriteId = CreateSprite("./images/Pong_ball.png", ball.width, ball.height, true);
				
			}
			if (scoreBlue == 10)
			{
				//Changing the txt to match new total and returning to main menu
				file.open("PlayerOneScore.txt", ios::out);
				playerOneHighscore++;
				file << playerOneHighscore << endl;
				file.sync();
				file.close();
				file.clear();
				eCurrentState = MENU;
				scoreBlue = 0;
			}
			if (scoreRed == 10)
			{
				//Changing the txt to match new total and returning to main menu
				scoreRed = 0;
				file.open("PlayerTwoScore.txt", ios::out);
				playerTwoHighscore++;
				file << playerTwoHighscore << endl;
				file.sync();
				file.close();
				file.clear();
				eCurrentState = MENU;;
				
			}
			//Ending for player's movements and ball movements
			playerOne.Move(fDeltaT, speed);
			playerTwo.Move(fDeltaT, speed);
			DrawSprite(playerOne.spriteId);
			DrawSprite(playerTwo.spriteId);
			DrawSprite(ball.spriteId);
			ClearScreen();
			break;

		}
		
		
	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}
