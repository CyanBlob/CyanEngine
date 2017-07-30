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

	position = {{-1.0, -1.0}, {1.0, 1.0}};

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

bool Player::playerCollision(location prevPosition,
			     GLfloat prevXOffset, GLfloat prevYOffset) {

	if (Collision::checkCollision(this))
	{
		position = prevPosition;

		xOffset = prevXOffset;
		yOffset = prevYOffset;
		return true;
	}

	return false;
}

// TODO: Cleanup collision checking code
void Player::playerAction(bool* keyStates)
{
	location prevPosition = position;
	GLfloat prevXOffset = xOffset;
	GLfloat prevYOffset = yOffset;

	if (keyStates['w'])
	{
		position.lowerLeft.y += speedForward;
		position.topRight.y += speedForward;
		yOffset -= speedForward;
		heading = 0;
	}
	else if (keyStates['s'])
	{
		position.lowerLeft.y += speedBack;
		position.topRight.y += speedBack;
		yOffset -= speedBack;
		heading = 2;
	}
	if (keyStates['w'] || keyStates['s']) {
		if (!playerCollision(prevPosition,
				     prevXOffset, prevYOffset)) {
			prevPosition = position;

			prevYOffset = yOffset;
		}
	}

	if (keyStates['a'])
	{
		position.lowerLeft.x += speedLeft;
		position.topRight.x += speedLeft;
		xOffset -= speedLeft;
		heading = 3;
	}
	else if (keyStates['d'])
	{
		position.lowerLeft.x += speedRight;
		position.topRight.x += speedRight;
		xOffset -= speedRight;
		heading = 1;
	}

	if (keyStates['a'] || keyStates['d']) {
		playerCollision(prevPosition,
				prevXOffset, prevYOffset);
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
	location attackPos = position;

	switch (heading) {
	case 0:
		attackPos.lowerLeft.y += 2;
		attackPos.topRight.y += 2;
		break;
	case 1:
		attackPos.topRight.x += 2;
		attackPos.lowerLeft.x += 2;
		break;
	case 2:
		attackPos.topRight.y -= 2;
		attackPos.lowerLeft.y -= 2;
		break;
	case 3:
		attackPos.topRight.x -= 2;
		attackPos.lowerLeft.x -= 2;
		break;
	default:
		break;
	}
	// TODO: free this
	Sword *sword = new Sword(attackPos);
}

void Player::addHealth(int amount) {
	health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	} else if (health <= 0) {
		// dead
	}
}

int Player::getHealth() {
	return health;
}

void Player::addStr(int amount) {
	strength += amount;
}

int Player::getStr() {
	return strength;
}

void Player::onCollisionEnter(Object *obj)
{
	//cout<<"Collided with: "<<obj->lowerLeft[0]<<","<<obj->lowerLeft[1]<<endl;
}
