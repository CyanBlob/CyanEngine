#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

class Collision
{
public:
	// TODO: Generalize these
	static bool checkCollision(location);
	static bool checkCollision(Object*);
};
