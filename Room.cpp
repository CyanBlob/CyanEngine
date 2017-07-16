#include "stdlib.h"
#include "Room.h"
#include "Collision.h"
#include "CyanPotion.h"

list<Room*> initopRightoomList()
{
	list<Room*> tmp;
	return tmp;
}
list <Room*> Room::roomList(initopRightoomList());

Room::Room(GLfloat _lowerLeft[], GLfloat _topRight[], GLfloat _wallSize)
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

GLfloat* Room::randomLocationInRoom() {
	GLfloat *ll = new GLfloat[2];
	ll[0] = rand() % (int)(((topRight[0]) - 2.0) - ((lowerLeft[0] + 2.0)));
	ll[1] = rand() % (int)(((topRight[1] - 2.0)) - ((lowerLeft[1] + 2.0)));
	ll[0] += lowerLeft[0] + 2.0;
	ll[1] += lowerLeft[1] + 2.0;
	return ll;
}

void Room::addItems() {
	// TODO: simplify this (why do I need _lowerLeft, not just ll = rand...)
	GLfloat *_lowerLeft = randomLocationInRoom();
	GLfloat ll[2] = {_lowerLeft[0], _lowerLeft[1]};
	GLfloat tr[2];
	tr[0] = ll[0] + 2.0;
	tr[1] = ll[1] + 2.0;
	Item::randomPotion(ll, tr);
	delete[] _lowerLeft;
}

void Room::buildRoom()
{
	GLfloat x;
	GLfloat color[3];
	Wall::randomColor(color);

	// TODO: Slap myself, and then fix these variable names
	GLfloat leftRightMiddle = ((topRight[1] - lowerLeft[1]) / 2.0f)
		+ lowerLeft[1];
	GLfloat leftRightMiddleLeft = leftRightMiddle - 2.5f;
	GLfloat leftRightMiddleRight = leftRightMiddle + 2.5f;

	GLfloat topBottomMiddle = ((topRight[0] - lowerLeft[0]) / 2.0f)
		+ lowerLeft[0];
	GLfloat topBottomMiddleLeft = topBottomMiddle - 2.5f;
	GLfloat topBottomMiddleRight = topBottomMiddle + 2.5f;


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
	this->addItems();
}
void Room::addToList(Room *room)
{
	if (room->roomFits)
	{
		Room::roomList.push_back(room);
	}
}
