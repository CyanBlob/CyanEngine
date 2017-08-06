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
	pos = _position;
	wallSize = _wallSize;

	if(!Collision::checkCollision(pos))
	{
		return;
	}

	roomFits = true;
}

location Room::randomLocationInRoom() {
    location _pos;
    _pos.ll.x = rand() %
        (int)(((pos.tr.x) - 2.0)
              - ((pos.ll.x + 2.0)));
    _pos.ll.y = rand() %
        (int)(((pos.tr.y - 2.0))
              - ((pos.ll.y + 2.0)));
    _pos.ll.x += pos.ll.x + 2.0;
    _pos.ll.y += pos.ll.y + 2.0;
    _pos.tr.x = _pos.ll.x + 2.0;
    _pos.tr.y = _pos.ll.y + 2.0;
    return _pos;
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
	GLfloat leftRightMiddle = ((pos.tr.y - pos.ll.y)
				   / 2.0f) + pos.ll.y;
	GLfloat leftRightMiddleLeft = leftRightMiddle - 2.5f;
	GLfloat leftRightMiddleRight = leftRightMiddle + 2.5f;

	GLfloat topBottomMiddle = ((pos.tr.x - pos.ll.x)
				   / 2.0f) + pos.ll.x;
	GLfloat topBottomMiddleLeft = topBottomMiddle - 2.5f;
	GLfloat topBottomMiddleRight = topBottomMiddle + 2.5f;


	// right and left
	for (x = pos.ll.y; x <= pos.tr.y; x += wallSize)
	{
		Wall *wall;

		// right wall
		if (!rightDoor || x < leftRightMiddleLeft
		    || x > leftRightMiddleRight)
		{
			location wallPosition =
			{{pos.tr.x, x},
			{pos.tr.x + wallSize, x + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);

		}
		// left wall
		if (!leftDoor || x < leftRightMiddleLeft
		    || x > leftRightMiddleRight)
		{
			location wallPosition =
			{{pos.ll.x, x},
			{pos.ll.x + wallSize, x + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);
		}

	}

	// bottom and top walls
	for (x = pos.ll.x; x <= pos.tr.x; x += wallSize)
	{
		Wall *wall;
		// bottom wall
		if (!bottomDoor || x < topBottomMiddleLeft
		    || x > topBottomMiddleRight)
		{
			location wallPosition =
			{{x, pos.ll.y},
			{x + wallSize, pos.ll.y + wallSize}};

			wall = new Wall(wallPosition);
			wall->addToList(wall);

		}

		// top wall
		if (!topDoor || x < topBottomMiddleLeft
		    || x > topBottomMiddleRight)
		{
			location wallPosition =
			{{x, pos.tr.y},
			{x + wallSize, pos.tr.y + wallSize}};

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
