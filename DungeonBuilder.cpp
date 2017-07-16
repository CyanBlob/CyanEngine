#include "DungeonBuilder.h"
#include "Room.h"

void DungeonBuilder::buildRooms(int maxRooms)
{
	int i;

	GLfloat roomLowerLeft[2] = {-8.0, -8.0};
	GLfloat roomTopRight[2] = {8.0, 8.0};

	Room *room = new Room(roomLowerLeft, roomTopRight, 2.0f);
	Room::addToList(room);

	for (i = 0; i < maxRooms; i++) {
		int j = 0;
		int roomOffset = rand() % Room::roomList.size();
		std::list<Room*>::iterator it;

		// pick a random room
		for (it = Room::roomList.begin();
		     it != Room::roomList.end() && j <= roomOffset; ++it, ++j);

		it--;
		/*cout<<j<<", "<<(*it)->lowerLeft[0]<<","<<(*it)->lowerLeft[1]
			<<", "<<(*it)->topRight[0]<<","<<(*it)->topRight[1]
			<<endl;*/

		GLfloat _roomLowerLeft[2];
		GLfloat _roomTopRight[2];

		int wall = rand() % 4;
		GLfloat size = rand() % 14;
		size = (size + 12) * 2;

		bool topDoor = false;
		bool rightDoor = false;
		bool bottomDoor = false;
		bool leftDoor = false;

		if (wall == 0)
		{
			bottomDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0];
			_roomLowerLeft[1] = (*it)->topRight[1] + 2.0f;
			_roomTopRight[0] = (*it)->topRight[0];
			_roomTopRight[1] = (*it)->topRight[1] + size;
		}
		else if (wall == 1)
		{
			leftDoor = true;
			_roomLowerLeft[0] = (*it)->topRight[0] + 2.0f;
			_roomLowerLeft[1] = (*it)->lowerLeft[1];
			_roomTopRight[0] = (*it)->topRight[0] + size;
			_roomTopRight[1] = (*it)->topRight[1];
		}
		else if (wall == 2)
		{
			topDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0];
			_roomLowerLeft[1] = (*it)->lowerLeft[1] - size;
			_roomTopRight[0] = (*it)->topRight[0];
			_roomTopRight[1] = (*it)->lowerLeft[1] - 2.0f;
		}
		else if (wall == 3)
		{
			rightDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0] - size;
			_roomLowerLeft[1] = (*it)->lowerLeft[1];
			_roomTopRight[0] = (*it)->lowerLeft[0] - 2.0f;
			_roomTopRight[1] = (*it)->topRight[1];
		}

		Room *_room = new Room(_roomLowerLeft, _roomTopRight, 2.0);
		if (_room->roomFits) {
			if (topDoor) {
				(*it)->bottomDoor = true;
				_room->topDoor = topDoor;
			}
			if (rightDoor) {
				(*it)->leftDoor = true;
				_room->rightDoor = rightDoor;
			}
			if (bottomDoor) {
				_room->bottomDoor = bottomDoor;
				(*it)->topDoor = true;
			}
			if (leftDoor) {
				_room->leftDoor = leftDoor;
				(*it)->rightDoor = true;
			}

			Room::addToList(_room);
		} else {
			delete(_room);
		}
	}
	// Build all rooms
	std::list<Room*>::iterator it;
	for (it = Room::roomList.begin(); it != Room::roomList.end(); ++it) {
		(*it)->buildRoom();
		// For debugging/demoing
		//display();
		//usleep(100000);
	}
	Object::objectLock.lock();
	Object::objectList.sort(Object::lessThan);
	Object::objectLock.unlock();
}
