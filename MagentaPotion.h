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

class MagentaPotion: public Item
{
public:
	MagentaPotion(location);
	~MagentaPotion(){};

	bool checkCollision(Object*);
	void onCollisionEnter(Object*);
	void destroy();
};
