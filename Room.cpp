#ifndef Included_Material_H
#define Included_Material_H
#include "Material.h"
#endif
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

Room::Room(location _position, GLfloat _wallSize = 2.0)
{
	position = _position;
	wallSize = _wallSize;

	if(!Collision::checkCollision(position))
	{
		return;
	}

	roomFits = true;
}

location Room::randomLocationInRoom() {
	location pos;
	pos.lowerLeft.x = rand() %
		(int)(((position.topRight.x) - 2.0)
		      - ((position.lowerLeft.x + 2.0)));
	pos.lowerLeft.y = rand() %
		(int)(((position.topRight.y - 2.0))
		      - ((position.lowerLeft.y + 2.0)));
	pos.lowerLeft.x += position.lowerLeft.x + 2.0;
	pos.lowerLeft.y += position.lowerLeft.y + 2.0;
	pos.topRight.x = pos.lowerLeft.x + 2.0;
	pos.topRight.y = pos.lowerLeft.y + 2.0;
	return pos;
}

void Room::addItems() {
	location randomPosition = randomLocationInRoom();
	Item::randomPotion(randomPosition);
}

void Room::addMaterials() {
	location randomPosition = randomLocationInRoom();
	Material::randomMaterial(randomPosition);
}

void Room::buildRoom()
{
	GLfloat x;
	GLfloat color[3];
	Wall::randomColor(color);

	// TODO: Slap myself, and then fix these variable names
	GLfloat leftRightMiddle = ((position.topRight.y - position.lowerLeft.y)
				   / 2.0f) + position.lowerLeft.y;
	GLfloat leftRightMiddleLeft = leftRightMiddle - 2.5f;
	GLfloat leftRightMiddleRight = leftRightMiddle + 2.5f;

	GLfloat topBottomMiddle = ((position.topRight.x - position.lowerLeft.x)
				   / 2.0f) + position.lowerLeft.x;
	GLfloat topBottomMiddleLeft = topBottomMiddle - 2.5f;
	GLfloat topBottomMiddleRight = topBottomMiddle + 2.5f;


	// right and left
	for (x = position.lowerLeft.y; x <= position.topRight.y; x += wallSize)
	{
		Wall *wall;

		// right wall
		if (!rightDoor || x < leftRightMiddleLeft
		    || x > leftRightMiddleRight)
		{
			location wallPosition =
			{{position.topRight.x, x},
			{position.topRight.x + wallSize, x + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);

		}
		// left wall
		if (!leftDoor || x < leftRightMiddleLeft
		    || x > leftRightMiddleRight)
		{
			location wallPosition =
			{{position.lowerLeft.x, x},
			{position.lowerLeft.x + wallSize, x + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);
		}

	}

	// bottom and top walls
	for (x = position.lowerLeft.x; x <= position.topRight.x; x += wallSize)
	{
		Wall *wall;
		// bottom wall
		if (!bottomDoor || x < topBottomMiddleLeft
		    || x > topBottomMiddleRight)
		{
			location wallPosition =
			{{x, position.lowerLeft.y},
			{x + wallSize, position.lowerLeft.y + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);

		}

		// top wall
		if (!topDoor || x < topBottomMiddleLeft
		    || x > topBottomMiddleRight)
		{
			location wallPosition =
			{{x, position.topRight.y},
			{x + wallSize, position.topRight.y + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);

		}
	}
	this->addItems();
	this->addMaterials();
}
void Room::addToList(Room *room)
{
	if (room->roomFits)
	{
		Room::roomList.push_back(room);
	}
}
