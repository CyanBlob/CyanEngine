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
	if (pos1.ll.x >= pos2.ll.x
	    && pos1.ll.x <= pos2.tr.x)
	{
		if (pos1.ll.y >= pos2.ll.y
		    && pos1.ll.y <= pos2.tr.y)
		{
			return true;
		}
	}

	if (pos1.tr.x >= pos2.ll.x
	    && pos1.tr.x <= pos2.tr.x)
	{
		if (pos1.tr.y >= pos2.ll.y
		    && pos1.tr.y <= pos2.tr.y)
		{
			return true;
		}
	}

	pos1 = {{pos1 .tr.x, pos1.ll.y},
		{pos1.ll.x, pos1.tr.y}};
	if (pos1.ll.x >= pos2.ll.x
	    && pos1.ll.x <= pos2.tr.x)
	{
		if (pos1.ll.y >= pos2.ll.y
		    && pos1.ll.y <= pos2.tr.y)
		{
			return true;
		}
	}

	if (pos1.tr.x >= pos2.ll.x
	    && pos1.tr.x <= pos2.tr.x)
	{
		if (pos1.tr.y >= pos2.ll.y
		    && pos1.tr.y <= pos2.tr.y)
		{
			return true;
		}
	}

	return false;
}

bool pointsOverlap(location pos1, location pos2)
{
	if (pos1.ll.x <= pos2.ll.x
	    && pos1.tr.x >= pos2.tr.x
	    && pos1.ll.y >= pos2.ll.y
	    && pos1.ll.y <= pos2.tr.y
	    && pos1.tr.y >= pos2.ll.y
	    && pos1.tr.y <= pos2.tr.y)
	{
		return true;
	}

	if (pos1.ll.y <= pos2.ll.y
	    && pos1.tr.y >= pos2.tr.y
	    && pos1.ll.x >= pos2.ll.x
	    && pos1.ll.x <= pos2.tr.x
	    && pos1.tr.x >= pos2.ll.x
	    && pos1.tr.x <= pos2.tr.x)
	{
		return true;
	}

	return false;
}

bool Collision::checkCollision(location pos)
{
	for (std::list<Room*>::iterator it=Room::roomList.begin();
	     it !=Room::roomList.end();
	     ++it)
	{
        if (pointEnclosed(pos, (*it)->pos))
		{
			return false;
		}

        if (pointEnclosed((*it)->pos, pos))
		{
			return false;
		}

        if (pointsOverlap(pos, (*it)->pos))
		{
			return false;
		}
	}
	return true;
}

// returns squared value for performance reasons
GLfloat pointDistance(location a, location b)
{
	return ((a.ll.x - b.ll.x)
		* (a.ll.x - b.ll.x)
		+ (a.ll.y - b.ll.y)
		* (a.ll.y - b.ll.y));
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

        if (pointDistance((*it)->pos, obj->pos) < 5.0)
		{
            if (pointEnclosed(obj->pos, (*it)->pos))
			{
				if (handleCollision((*it), obj)) {
					return true;
				}
			}

            if (pointEnclosed((*it)->pos, obj->pos))
			{
				if (handleCollision((*it), obj)) {
					return true;
				}
			}

            if (pointsOverlap(obj->pos, (*it)->pos))
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
