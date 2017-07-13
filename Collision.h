#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

class Collision
{
public:
	// TODO: Generalize these
	static bool checkCollision(GLfloat[2], GLfloat[2]);
	static bool checkCollision(Object*);
};
