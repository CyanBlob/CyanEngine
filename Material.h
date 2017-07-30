#ifndef Included_Item_H
#define Included_Item_H
#include "Item.h"
#endif

#include <iostream>
#include <list>

#include "InventoryManager.h"

using namespace std;

class Material: public Item
{
public:
	Material(location);
	~Material(){};
	static void randomMaterial(location);
	void addToInventory();
};
