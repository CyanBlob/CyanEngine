#include "Room.h"

list<Room*> initRoomList()
{
	list<Room*> tmp;
	return tmp;
}
list <Room*> Room::roomList(initRoomList());

Room::Room(GLfloat _lowerLeft[], GLfloat _topRight[], GLfloat wallSize)
{
	GLfloat x;

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _topRight[0];
	topRight[1] = _topRight[1];

	cout<<"Building room from "<<_lowerLeft[0]<<", "<<_lowerLeft[1]<<" to "<<
		topRight[0]<<", "<<topRight[1]<<endl;

	if(!checkIfFits())
	{
		return;
	}

	// right and left
	for (x = lowerLeft[1]; x <= topRight[1]; x += wallSize)
	{
		// right wall
		GLfloat tmpWallCoords[3] = {topRight[0], x, 0.0};

		Wall *wall = new Wall(tmpWallCoords, wallSize);
		wall->addToList(wall);

		// left wall
		GLfloat tmpWallCoordsLL[3] = {lowerLeft[0], x, 0.0};

		wall = new Wall(tmpWallCoordsLL, wallSize);
		wall->addToList(wall);

	}

	// bottom and top walls
	for (x = lowerLeft[0]; x <= topRight[0]; x += wallSize)
	{
		// bottom wall
		GLfloat tmpWallCoords[3] = {x, lowerLeft[1], 0.0};

		Wall *wall = new Wall(tmpWallCoords, wallSize);
		wall->addToList(wall);

		// top wall
		GLfloat tmpWallCoordsLL[3] = {x, topRight[1], 0.0};

		wall = new Wall(tmpWallCoordsLL, wallSize);
		wall->addToList(wall);
	}
}
void Room::addToList(Room *room)
{
	cout<<"Adding room from: "<<room->lowerLeft[0]<<", "<<room->lowerLeft[1]
		<<", to "<<room->topRight[0]<<", "<<room->topRight[1]<<endl;
	Room::roomList.push_front(room);
}

bool Room::checkIfFits()
{
	int i;

	// TODO: Research C++ iterators
	for (std::list<Room*>::iterator it=roomList.begin(); it !=roomList.end(); ++it)
	{
		cout<<"Checking room against: "<<(*it)->lowerLeft[0]<<", "<<(*it)->lowerLeft[1]
			<<", to "<<(*it)->topRight[0]<<", "<<(*it)->topRight[1]<<endl;

		if ((lowerLeft[0] == (*it)->lowerLeft[0]) && !(lowerLeft[1] >= (*it)->topRight[1]))
		{
			cout<<"Room does NOT fit. lowerLeft on left wall of another room"<<endl;
			return false;
		}

		if ((topRight[1] == (*it)->topRight[1]) && !(topRight[0] <= (*it)->lowerLeft[0]))
		{
			cout<<"Room does NOT fit. topRight on top wall of another room"<<endl;
			return false;
		}

		//TODO: Add check for new room "enclosing" another room
		if ((lowerLeft[0] > (*it)->lowerLeft[0] && lowerLeft[0] < (*it)->topRight[0]
		    && lowerLeft[1] > (*it)->lowerLeft[1] && lowerLeft[1] < (*it)->topRight[1])
		    || (topRight[0] > (*it)->lowerLeft[0] && topRight[0] < (*it)->topRight[0]
		    && topRight[1] > (*it)->lowerLeft[1] && topRight[1] < (*it)->topRight[1]))
		{
			cout<<"Room does NOT fit"<<endl;
			return false;
		}
	}
	cout<<"Room fits!"<<endl;
	return true;
}
