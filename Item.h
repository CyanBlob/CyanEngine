#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

#include <iostream>

using namespace std;

class Item: public Object
{
public:
	Item(GLfloat[2], GLfloat[2]);

	void onPickUp();
	bool checkCollision(Object*);
	void onCollisionEnter(Object*);
};
