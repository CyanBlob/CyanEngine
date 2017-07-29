#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

#include <iostream>
#include <list>
#ifndef Included_Item_H
#define Included_Item_H
#include "Item.h"
#endif

using namespace std;

class CyanPotion: public Item
{
public:
	CyanPotion(location);
	~CyanPotion(){};

	bool checkCollision(Object*);
	void onCollisionEnter(Object*);
	void destroy();
};
