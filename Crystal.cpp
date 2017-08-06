#ifndef Included_Crystal_H
#define Included_Crystal_H
#include "Crystal.h"
#endif
#include <iostream>

Crystal::Crystal(location _position) : Material(_position)
{
	pos = _position;

	imageFile = "resources/crawl_tiles/item/misc/misc_crystal.png";
	colliderType = ITEM;
}

bool Crystal::checkCollision(Object *obj)
{
}
void Crystal::onCollisionEnter(Object *obj)
{
	this->destroy();
}
void Crystal::destroy()
{
	// only called from Collision.cpp, which already locked ObjectLock
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it != Object::objectList.end(); ++it)
	{
		if ((*it) == this)
		{
			Object::objectList.erase(it);
			delete(*it);
			break;
		}
	}
}
