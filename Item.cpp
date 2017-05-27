#include "Item.h"

Item::Item(GLfloat _lowerLeft[2], GLfloat _topRight[2])
{
	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _topRight[0];
	topRight[1] = _topRight[1];

	imageFile = "resources/crawl_tiles/item/potion/cyan.png";
}

bool Item::checkCollision(Object *obj)
{
	cout<<"Not implemented"<<endl;
	return false;
}

void Item::onCollisionEnter(Object *obj)
{
	cout<<"Collided with: "<<obj->lowerLeft[0]<<","<<obj->lowerLeft[1]<<endl;
}
