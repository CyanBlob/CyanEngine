#include "Player.h"
#include "Collision.h"
using namespace std;

Player::Player() : mainRect{ // Only works in C++11
		 {-1.0, 1.0, 0.0},
		 {1.0, 1.0, 0.0},
		 {1.0, -1.0, 0.0},
		 {-1.0, -1.0, 0.0}}
{
	// Player speed
	speedForward = 0.2f;
	speedBack = -0.2f;
	speedRight = 0.2f;
	speedLeft = -0.2f;
}
void Player::copyGLfloatArray(GLfloat array1[], GLfloat array2[])
{
	int i;

	for (i = 0; i <= (int) (sizeof array1[0] / sizeof array1[0]); i++)
	{
		if (i <= (int) (sizeof array2[0] / sizeof array2[0]))
		{
			array2[i] = array1[i];
		}
		else
		{
			return;
		}
	}
}

bool Player::playerCollision(GLfloat prevPosition[4][3], GLfloat prevXOffset,
		     GLfloat prevYOffset) {
	int i, j;
	// TODO: Don't revert movements on non-blocked axis if two keys are held
	if (!Collision::checkPlayerCollision(mainRect[3], mainRect[1]))
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				mainRect[i][j] = prevPosition[i][j];
			}
		}
		xOffset = prevXOffset;
		yOffset = prevYOffset;
	}
}

// TODO: Cleanup collision checking code
void Player::playerAction(bool* keyStates)
{
	int i, j;
	GLfloat prevPosition[4][3];
	GLfloat prevXOffset = xOffset;
	GLfloat prevYOffset = yOffset;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			prevPosition[i][j] = mainRect[i][j];
		}
	}

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

	playerCollision(prevPosition, prevXOffset, prevYOffset);


	if (keyStates[32])
	{
		// TODO: Implement a timer here (check time difference)
		if (playerAttacking)
		{
			stopAttack();
		}
		else
		{
			attack();
		}
	}

}

void Player::stopAttack()
{
	playerAttacking = false;
	GLfloat tmpColor[3] = {color[0], color[1], color[2]};
	copyGLfloatArray(flashColor, color);
	copyGLfloatArray(tmpColor, flashColor);
}

void Player::attack()
{
	playerAttacking = true;
	GLfloat tmpColor[3] = {color[0], color[1], color[2]};
	copyGLfloatArray(flashColor, color);
	copyGLfloatArray(tmpColor, flashColor);
}

