#include "Collision.h"
#include "SOIL.h"
using namespace std;

Player::Player()
{
	imageFile = "resources/crawl_tiles/player/transform/lich_form.png";

	lowerLeft[0] = -1.0;
	lowerLeft[1] = -1.0;
	topRight[0] = 1.0;
	topRight[1] = 1.0;

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

bool Player::playerCollision(GLfloat prevLowerLeft[2], GLfloat prevTopRight[2],
			     GLfloat prevXOffset, GLfloat prevYOffset) {

	if (!Collision::checkPlayerCollision(this))
	{
		lowerLeft[0] = prevLowerLeft[0];
		lowerLeft[1] = prevLowerLeft[1];
		topRight[0] = prevTopRight[0];
		topRight[1] = prevTopRight[1];

		xOffset = prevXOffset;
		yOffset = prevYOffset;
		return true;
	}

	return false;
}

// TODO: Cleanup collision checking code
void Player::playerAction(bool* keyStates)
{
	GLfloat prevLowerLeft[2] = {lowerLeft[0], lowerLeft[1]};
	GLfloat prevTopRight[2] = {topRight[0], topRight[1]};
	GLfloat prevXOffset = xOffset;
	GLfloat prevYOffset = yOffset;

	if (keyStates['w'])
	{
		int i;
		lowerLeft[1] += speedForward;
		topRight[1] += speedForward;
		yOffset -= speedForward;
	}
	else if (keyStates['s'])
	{
		int i;
		lowerLeft[1] += speedBack;
		topRight[1] += speedBack;
		yOffset -= speedBack;
	}
	if (!playerCollision(prevLowerLeft, prevTopRight,
			     prevXOffset, prevYOffset)) {
		prevLowerLeft[0] = lowerLeft[0];
		prevLowerLeft[1] = lowerLeft[1];
		prevTopRight[0] = topRight[0];
		prevTopRight[1] = topRight[1];

		prevYOffset = yOffset;
	}

	if (keyStates['a'])
	{
		int i;
		lowerLeft[0] += speedLeft;
		topRight[0] += speedLeft;
		xOffset -= speedLeft;
	}
	else if (keyStates['d'])
	{
		int i;
		lowerLeft[0] += speedRight;
		topRight[0] += speedRight;
		xOffset -= speedRight;
	}

	playerCollision(prevLowerLeft, prevTopRight, prevXOffset, prevYOffset);

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
