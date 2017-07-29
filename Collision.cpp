#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glut.h>
#include <stdio.h>

#include "Collision.h"
#include "Room.h"
#include "Item.h"

bool pointEnclosed(location pos1, location pos2)
{
	if (pos1.lowerLeft.x >= pos2.lowerLeft.x
	    && pos1.lowerLeft.x <= pos2.topRight.x)
	{
		if (pos1.lowerLeft.y >= pos2.lowerLeft.y
		    && pos1.lowerLeft.y <= pos2.topRight.y)
		{
			return true;
		}
	}

	if (pos1.topRight.x >= pos2.lowerLeft.x
	    && pos1.topRight.x <= pos2.topRight.x)
	{
		if (pos1.topRight.y >= pos2.lowerLeft.y
		    && pos1.topRight.y <= pos2.topRight.y)
		{
			return true;
		}
	}

	pos1 = {{pos1 .topRight.x, pos1.lowerLeft.y},
		{pos1.lowerLeft.x, pos1.topRight.y}};
	if (pos1.lowerLeft.x >= pos2.lowerLeft.x
	    && pos1.lowerLeft.x <= pos2.topRight.x)
	{
		if (pos1.lowerLeft.y >= pos2.lowerLeft.y
		    && pos1.lowerLeft.y <= pos2.topRight.y)
		{
			return true;
		}
	}

	if (pos1.topRight.x >= pos2.lowerLeft.x
	    && pos1.topRight.x <= pos2.topRight.x)
	{
		if (pos1.topRight.y >= pos2.lowerLeft.y
		    && pos1.topRight.y <= pos2.topRight.y)
		{
			return true;
		}
	}

	return false;
}

bool pointsOverlap(location pos1, location pos2)
{
	if (pos1.lowerLeft.x <= pos2.lowerLeft.x
	    && pos1.topRight.x >= pos2.topRight.x
	    && pos1.lowerLeft.y >= pos2.lowerLeft.y
	    && pos1.lowerLeft.y <= pos2.topRight.y
	    && pos1.topRight.y >= pos2.lowerLeft.y
	    && pos1.topRight.y <= pos2.topRight.y)
	{
		return true;
	}

	if (pos1.lowerLeft.y <= pos2.lowerLeft.y
	    && pos1.topRight.y >= pos2.topRight.y
	    && pos1.lowerLeft.x >= pos2.lowerLeft.x
	    && pos1.lowerLeft.x <= pos2.topRight.x
	    && pos1.topRight.x >= pos2.lowerLeft.x
	    && pos1.topRight.x <= pos2.topRight.x)
	{
		return true;
	}

	return false;
}

bool Collision::checkCollision(location position)
{
	for (std::list<Room*>::iterator it=Room::roomList.begin();
	     it !=Room::roomList.end();
	     ++it)
	{
		if (pointEnclosed(position, (*it)->position))
		{
			return false;
		}

		if (pointEnclosed((*it)->position, position))
		{
			return false;
		}

		if (pointsOverlap(position, (*it)->position))
		{
			return false;
		}
	}
	return true;
}

// returns squared value for performance reasons
GLfloat pointDistance(location a, location b)
{
	return ((a.lowerLeft.x - b.lowerLeft.x)
		* (a.lowerLeft.x - b.lowerLeft.x)
		+ (a.lowerLeft.y - b.lowerLeft.y)
		* (a.lowerLeft.y - b.lowerLeft.y));
}

bool handleCollision(Object *obj1, Object *obj2) {
	int collide1 = obj1->colliderType & obj2->collidesWith;
	int collide2 = obj2->colliderType & obj1->collidesWith;

	if ((collide1 > 0) || (collide2 > 0)) {
		obj1->onCollisionEnter(obj2);
		obj2->onCollisionEnter(obj1);
		Object::objectLock.unlock();
		return true;
	}
	Object::objectLock.unlock();
	return false;
}

// TODO: support multiple collisions
bool Collision::checkCollision(Object *obj)
{
	Object::objectLock.lock();
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it != Object::objectList.end();
	     ++it)
	{
		// objects shouldn't collide with themselves
		if (obj == (*it)) {
			continue;
		}

		if (pointDistance((*it)->position, obj->position) < 5.0)
		{
			if (pointEnclosed(obj->position, (*it)->position))
			{
				if (handleCollision((*it), obj)) {
					return true;
				}
			}

			if (pointEnclosed((*it)->position, obj->position))
			{
				if (handleCollision((*it), obj)) {
					return true;
				}
			}

			if (pointsOverlap(obj->position, (*it)->position))
			{
				if (handleCollision((*it), obj)) {
					return true;
				}
			}
		}
	}
	Object::objectLock.unlock();
	return false;
}
