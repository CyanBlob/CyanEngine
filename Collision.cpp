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

bool pointEnclosed(GLfloat point[2], GLfloat _lowerLeft[2], GLfloat _topRight[2])
{
	if (point[0] >= _lowerLeft[0] && point[0] <= _topRight[0])
	{
		if (point[1] >= _lowerLeft[1] && point[1] <= _topRight[1])
		{
			return true;
		}
	}
	return false;
}

bool pointsOverlap(GLfloat lowerLeft[2], GLfloat topRight[2],
		   GLfloat _lowerLeft[2], GLfloat _topRight[2])
{
	if (lowerLeft[0] <= _lowerLeft[0]
	    && topRight[0] >= _topRight[0]
	    && lowerLeft[1] >= _lowerLeft[1]
	    && lowerLeft[1] <= _topRight[1]
	    && topRight[1] >= _lowerLeft[1]
	    && topRight[1] <= _topRight[1])
	{
		return true;
	}

	if (lowerLeft[1] <= _lowerLeft[1]
	    && topRight[1] >= _topRight[1]
	    && lowerLeft[0] >= _lowerLeft[0]
	    && lowerLeft[0] <= _topRight[0]
	    && topRight[0] >= _lowerLeft[0]
	    && topRight[0] <= _topRight[0])
	{
		return true;
	}

	return false;
}

bool Collision::checkCollision(GLfloat lowerLeft[2], GLfloat topRight[2])
{
	for (std::list<Room*>::iterator it=Room::roomList.begin();
	     it !=Room::roomList.end();
	     ++it)
	{
		GLfloat lowerRight[2] = {topRight[0], lowerLeft[1]};
		GLfloat topLeft[2] = {lowerLeft[0], topRight[1]};

		//TODO: Add check for new room "enclosing" another room
		if (pointEnclosed(lowerLeft,
				  (*it)->lowerLeft, (*it)->topRight)
		    || pointEnclosed(topRight,
				     (*it)->lowerLeft, (*it)->topRight)
		    || pointEnclosed(lowerRight,
				     (*it)->lowerLeft, (*it)->topRight)
		    || pointEnclosed(topLeft,
				     (*it)->lowerLeft, (*it)->topRight))
		{
			//cout<<"Point enclosed by points"<<endl;
			return false;
		}

		GLfloat _lowerRight[2] = {(*it)->topRight[0],
			(*it)->lowerLeft[1]};
		GLfloat _topLeft[2] = {(*it)->lowerLeft[0],
			(*it)->topRight[1]};

		if (pointEnclosed((*it)->lowerLeft, lowerLeft, topRight)
		    || pointEnclosed((*it)->topRight, lowerLeft, topRight)
		    || pointEnclosed(_lowerRight, lowerLeft, topRight)
		    || pointEnclosed(_topLeft, lowerLeft, topRight))
		{
			//cout<<"Point encloses other points"<<endl;
			return false;
		}

		if (pointsOverlap(lowerLeft, topRight,
				  (*it)->lowerLeft, (*it)->topRight))
		{
			//cout<<"Rooms overlap"<<endl;
			return false;
		}
	}
	//cout<<"Room fits!"<<endl;
	//roomBuilt = true;
	return true;
}

// returns squared value for performance reasons
GLfloat pointDistance(GLfloat a[2], GLfloat b[2])
{
	return ((a[0] - b[0]) * (a[0] - b[0])
		+ (a[1] - b[1]) * (a[1] - b[1]));
}

bool handleCollision(Object *obj1, Object *obj2) {
	int collide1 = obj1->colliderType & obj2->collidesWith;
	int collide2 = obj2->colliderType & obj1->collidesWith;

	if ((collide1 > 0) || (collide2 > 0)) {
		obj1->onCollisionEnter(obj2);
		obj2->onCollisionEnter(obj1);
		Object::objectLock.unlock();
		return false;
	}
	Object::objectLock.unlock();
	return true;
}

// TODO: support multiple collisions
bool Collision::checkPlayerCollision(Object *obj)
{
	GLfloat lowerLeft[2] = {obj->lowerLeft[0], obj->lowerLeft[1]};
	GLfloat topRight[2] = {obj->topRight[0], obj->topRight[1]};

	Object::objectLock.lock();
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it != Object::objectList.end();
	     ++it)
	{
		// objects shouldn't collide with themselves
		if (obj == (*it)) {
			continue;
		}

		if (pointDistance((*it)->lowerLeft, obj->lowerLeft) < 5.0)
		{
			GLfloat lowerRight[2] = {topRight[0], lowerLeft[1]};
			GLfloat topLeft[2] = {lowerLeft[0], topRight[1]};

			if (pointEnclosed(lowerLeft,
					  (*it)->lowerLeft, (*it)->topRight)
			    || pointEnclosed(topRight,
					     (*it)->lowerLeft, (*it)->topRight)
			    || pointEnclosed(lowerRight,
					     (*it)->lowerLeft, (*it)->topRight)
			    || pointEnclosed(topLeft,
					     (*it)->lowerLeft, (*it)->topRight))
			{
				return handleCollision((*it), obj);
			}

			GLfloat _lowerRight[2] = {(*it)->topRight[0],
				(*it)->lowerLeft[1]};
			GLfloat _topLeft[2] = {(*it)->lowerLeft[0],
				(*it)->topRight[1]};

			if (pointEnclosed((*it)->lowerLeft, lowerLeft, topRight)
			    || pointEnclosed((*it)->topRight, lowerLeft, topRight)
			    || pointEnclosed(_lowerRight, lowerLeft, topRight)
			    || pointEnclosed(_topLeft, lowerLeft, topRight))
			{
				return handleCollision((*it), obj);
			}

			if (pointsOverlap(lowerLeft, topRight,
					  (*it)->lowerLeft, (*it)->topRight))
			{
				return handleCollision((*it), obj);
			}
		}
	}
	Object::objectLock.unlock();
	return true;
}
