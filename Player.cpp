#include "Collision.h"
#include "SOIL.h"
#include "Wall.h"
#include "Sword.h"
#include "Player.h"
#include <chrono>

using namespace std;

Player::Player()
{
	tag = "player";
	imageFile = "resources/crawl_tiles/player/transform/lich_form.png";
	colliderType = PLAYER;
	collidesWith = ITEM | ENVIRONMENT;

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

	if (Collision::checkCollision(this))
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
		lowerLeft[1] += speedForward;
		topRight[1] += speedForward;
		yOffset -= speedForward;
		heading = 0;
	}
	else if (keyStates['s'])
	{
		lowerLeft[1] += speedBack;
		topRight[1] += speedBack;
		yOffset -= speedBack;
		heading = 2;
	}
	if (keyStates['w'] || keyStates['s']) {
		if (!playerCollision(prevLowerLeft, prevTopRight,
				     prevXOffset, prevYOffset)) {
			prevLowerLeft[0] = lowerLeft[0];
			prevLowerLeft[1] = lowerLeft[1];
			prevTopRight[0] = topRight[0];
			prevTopRight[1] = topRight[1];

			prevYOffset = yOffset;
		}
	}

	if (keyStates['a'])
	{
		lowerLeft[0] += speedLeft;
		topRight[0] += speedLeft;
		xOffset -= speedLeft;
		heading = 3;
	}
	else if (keyStates['d'])
	{
		lowerLeft[0] += speedRight;
		topRight[0] += speedRight;
		xOffset -= speedRight;
		heading = 1;
	}

	if (keyStates['a'] || keyStates['d']) {
		playerCollision(prevLowerLeft, prevTopRight, prevXOffset, prevYOffset);
	}

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
	if (std::chrono::system_clock::now().time_since_epoch().count()
	       < attackTime + attackDelay)
	{
		return;
	}
	attackTime =
		std::chrono::system_clock::now().time_since_epoch().count();

	playerAttacking = true;
	GLfloat tmpColor[3] = {color[0], color[1], color[2]};
	copyGLfloatArray(flashColor, color);
	copyGLfloatArray(tmpColor, flashColor);
	GLfloat color[3] = {.5, .5, .5};
	GLfloat position[2];
	GLfloat size = 2.0;

	switch (heading) {
	case 0:
		position[0] = lowerLeft[0];
		position[1] = lowerLeft[1] + 2;
		break;
	case 1:
		position[0] = lowerLeft[0] + 2;
		position[1] = lowerLeft[1];
		break;
	case 2:
		position[0] = lowerLeft[0];
		position[1] = lowerLeft[1] - 2;
		break;
	case 3:
		position[0] = lowerLeft[0] - 2;
		position[1] = lowerLeft[1];
		break;
	default:
		position[0] = lowerLeft[0];
		position[1] = lowerLeft[1];
		break;
	}
	Sword *sword = new Sword(position, size);
}

void Player::addHealth(int amount) {
	health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	} else if (health <= 0) {
		// dead
	}
}

void Player::onCollisionEnter(Object *obj)
{
	//cout<<"Collided with: "<<obj->lowerLeft[0]<<","<<obj->lowerLeft[1]<<endl;
}
