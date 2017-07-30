#include "stdlib.h"
#include "CyanPotion.h"
#include "MagentaPotion.h"

void randomColor(GLfloat _color[]);

void Item::randomPotion(location _position) {
	int randInt = rand() % 10;
	if (randInt == 0) {
		new MagentaPotion(_position);
	} else {
		new CyanPotion(_position);
	}
}

Item::Item(location _position)
{
	position = _position;

	//imageFile = "resources/crawl_tiles/item/potion/cyan.png";
	colliderType = ITEM;


	Object::objectLock.lock();
	Object::objectList.push_back(this);
	Object::objectLock.unlock();
}
