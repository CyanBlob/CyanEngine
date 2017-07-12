#include "Item.h"

void randomColor(GLfloat _color[]);

Item::Item(GLfloat _lowerLeft[2], GLfloat _topRight[2])
{
	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _topRight[0];
	topRight[1] = _topRight[1];

	imageFile = "resources/crawl_tiles/item/potion/cyan.png";
	colliderType = ITEM;


	Object::objectLock.lock();
	Object::objectList.push_back(this);
	Object::objectLock.unlock();
}
