#ifndef Included_Player_H
#define Included_Player_H
#include "Player.h"
#endif

class Collision
{
public:
	// TODO: Generalize these
	static bool checkCollision(GLfloat[2], GLfloat[2]);
	static bool checkPlayerCollision(Object*);
};
