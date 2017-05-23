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

	if(!Collision::checkCollision(lowerLeft, topRight))
	{
		return;
	}

	roomFits = true;
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
		Wall *wall;

		// right wall
		if (!rightDoor || x < leftRightMiddleLeft
		    || x > leftRightMiddleRight) {
			GLfloat tmpWallCoords[3] = {topRight[0], x, 0.0};

			wall = new Wall(tmpWallCoords, wallSize, color);
			wall->addToList(wall);

		}
		// left wall
		if (!leftDoor || x < leftRightMiddleLeft
		    || x > leftRightMiddleRight) {
			GLfloat tmpWallCoordsLL[3] = {lowerLeft[0], x, 0.0};

			wall = new Wall(tmpWallCoordsLL, wallSize, color);
			wall->addToList(wall);
		}

	}

	// bottom and top walls
	for (x = lowerLeft[0]; x <= topRight[0]; x += wallSize)
	{
		Wall *wall;
		// bottom wall
		if (!bottomDoor || x < topBottomMiddleLeft
		    || x > topBottomMiddleRight) {
		GLfloat tmpWallCoords[3] = {x, lowerLeft[1], 0.0};

		wall = new Wall(tmpWallCoords, wallSize, color);
		wall->addToList(wall);
		}

		// top wall
		if (!topDoor || x < topBottomMiddleLeft
		    || x > topBottomMiddleRight) {
			GLfloat tmpWallCoordsLL[3] = {x, topRight[1], 0.0};

			wall = new Wall(tmpWallCoordsLL, wallSize, color);
			wall->addToList(wall);
		}
	}
}
void Room::addToList(Room *room)
{
	if (roomFits)
	{
		Room::roomList.push_back(room);
	}
}
