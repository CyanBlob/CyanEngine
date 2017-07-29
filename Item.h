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
	Item(location);
	~Item(){};

	static Object* randomPotion(location);
	virtual bool checkCollision(Object*) = 0;
	virtual void onCollisionEnter(Object*) = 0;
	virtual void destroy() = 0;
};
