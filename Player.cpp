#include "Player.h"
#include "Collision.h"
#include "SOIL.h"
using namespace std;

Player::Player() : mainRect{ // Only works in C++11
		 {-1.0, 1.0, 0.0},
		 {1.0, 1.0, 0.0},
		 {1.0, -1.0, 0.0},
		 {-1.0, -1.0, 0.0}}
{
	imageFile = "resources/crawl_tiles/player/transform/lich_form.png";
	// Player speed
	speedForward = 0.2f;
	speedBack = -0.2f;
	speedRight = 0.2f;
	speedLeft = -0.2f;

	lowerLeft[0] = mainRect[3][0];
	lowerLeft[1] = mainRect[3][1];
	topRight[0] = mainRect[1][0];
	topRight[1] = mainRect[1][1];
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
		return true;
	}
	return false;
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
	if (!playerCollision(prevPosition, prevXOffset, prevYOffset)) {
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
			{
				prevPosition[i][j] = mainRect[i][j];
			}
		}
		prevYOffset = yOffset;
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

void Player::onCollisionEnter(Object *obj)
{
	cout<<"Collided with: "<<obj->lowerLeft[0]<<","<<obj->lowerLeft[1]<<endl;
}
