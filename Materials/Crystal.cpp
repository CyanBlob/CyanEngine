#ifndef Included_Crystal_H
#define Included_Crystal_H
#include "Crystal.h"
#endif

Crystal::Crystal(location _position) : Material(_position)
{
	position = _position;

	imageFile = "../resources/crawl_tiles/item/misc/misc_crystal.png";
	colliderType = ITEM;


	Object::objectLock.lock();
	Object::objectList.push_back(this);
	Object::objectLock.unlock();
}
