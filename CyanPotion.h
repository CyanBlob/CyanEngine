#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

#include <iostream>
#include <list>
#include "Item.h"

using namespace std;

class CyanPotion: public Item
{
public:
	CyanPotion(GLfloat[2], GLfloat[2]);
	~CyanPotion(){};

	bool checkCollision(Object*);
	void onCollisionEnter(Object*);
	void destroy();
};
