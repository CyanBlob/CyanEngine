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

// TODO: Simplify tests
bool Collision::checkCollision(GLfloat lowerLeft[2], GLfloat topRight[2])
{
	// TODO: Research C++ iterators
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
