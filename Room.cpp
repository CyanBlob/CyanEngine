#include "Room.h"
#include "Collision.h"

list<Room*> initopRightoomList()
{
	list<Room*> tmp;
	return tmp;
}
list <Room*> Room::roomList(initopRightoomList());

Room::Room(int _lowerLeft[], int _topRight[], GLfloat _wallSize)
{

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _topRight[0];
	topRight[1] = _topRight[1];

	wallSize = _wallSize;

	//cout<<"Building room from "<<_lowerLeft[0]<<", "<<_lowerLeft[1]<<" to "<<
		//topRight[0]<<", "<<topRight[1]<<endl;

	if(!Collision::checkCollision(lowerLeft, topRight))
	{
		return;
	}
	roomBuilt = true;
}

void Room::buildRoom()
{
	GLfloat x;
	GLfloat color[3];
	Wall::randomColor(color);

	// TODO: Slap myself, and then fix these variable names
	GLfloat leftRightMiddle = ((topRight[1] - lowerLeft[1]) / 2)
		+ lowerLeft[1];
	GLfloat leftRightMiddleLeft = leftRightMiddle - 2.5;
	GLfloat leftRightMiddleRight = leftRightMiddle + 2.5;

	GLfloat topBottomMiddle = ((topRight[0] - lowerLeft[0]) / 2)
		+ lowerLeft[0];
	GLfloat topBottomMiddleLeft = topBottomMiddle - 2.5;
	GLfloat topBottomMiddleRight = topBottomMiddle + 2.5;


	// right and left
	for (x = lowerLeft[1]; x <= topRight[1]; x += wallSize)
	{
		// right wall
		if (rightDoor && x > leftRightMiddleLeft
		    && x < leftRightMiddleRight) {
			continue;
		}
		GLfloat tmpWallCoords[3] = {topRight[0], x, 0.0};

		Wall *wall = new Wall(tmpWallCoords, wallSize, color);
		wall->addToList(wall);

		// left wall
		if (leftDoor && x > leftRightMiddleLeft
		    && x < leftRightMiddleRight) {
			continue;
		}
		GLfloat tmpWallCoordsLL[3] = {lowerLeft[0], x, 0.0};

		wall = new Wall(tmpWallCoordsLL, wallSize, color);
		wall->addToList(wall);

	}

	// bottom and top walls
	for (x = lowerLeft[0]; x <= topRight[0]; x += wallSize)
	{
		// bottom wall
		if (bottomDoor && x > topBottomMiddleLeft
		    && x < topBottomMiddleRight) {
			continue;
		}
		GLfloat tmpWallCoords[3] = {x, lowerLeft[1], 0.0};

		Wall *wall = new Wall(tmpWallCoords, wallSize, color);
		wall->addToList(wall);

		// top wall
		if (topDoor && x > topBottomMiddleLeft
		    && x < topBottomMiddleRight) {
			continue;
		}
		GLfloat tmpWallCoordsLL[3] = {x, topRight[1], 0.0};

		wall = new Wall(tmpWallCoordsLL, wallSize, color);
		wall->addToList(wall);
	}
}
void Room::addToList(Room *room)
{
	if (roomBuilt)
	{
		Room::roomList.push_front(room);
	}
}

/*bool pointEnclosed(GLfloat point[2], GLfloat _lowerLeft[2], GLfloat _topRight[2])
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
bool Room::checkIfFits()
{
// TODO: Research C++ iterators
for (std::list<Room*>::iterator it=roomList.begin(); it !=roomList.end();
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
	roomBuilt = true;
	return true;
}*/
