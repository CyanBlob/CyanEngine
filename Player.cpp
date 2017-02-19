#include "Player.h"
using namespace std;

Player::Player() : mainRect{ // Only works in C++11
		 {-1.0, 1.0, 0.0},
		 {1.0, 1.0, 0.0},
		 {1.0, -1.0, 0.0},
		 {-1.0, -1.0, 0.0}}
{
	// Player speed
	speedForward = 0.1f;
	speedBack = -0.1f;
	speedRight = 0.1f;
	speedLeft = -0.1f;
}

void Player::playerAction(bool* keyStates)
{
	//cout<<keyStates['w']<<endl;
	if (keyStates['w'])
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			mainRect[i][1] += speedForward;
		}
		yOffset -= speedForward;
	}
	else if (keyStates['s'])
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			mainRect[i][1] += speedBack;
		}
		yOffset -= speedBack;
	}
	if (keyStates['a'])
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			mainRect[i][0] += speedLeft;
		}
		xOffset -= speedLeft;
	}
	else if (keyStates['d'])
	{
		int i;
		for (i = 0; i < 4; i++)
		{
			mainRect[i][0] += speedRight;
		}
		xOffset -= speedRight;
	}

}
