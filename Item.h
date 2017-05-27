#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

#include <iostream>
#include <list>

using namespace std;

class Item: public Object
{
public:
	Item(GLfloat[2], GLfloat[2]);
	~Item(){};

	static list<Item*> itemList;

	void onPickUp();
	bool checkCollision(Object*);
	void onCollisionEnter(Object*);
	void destroy();
};
