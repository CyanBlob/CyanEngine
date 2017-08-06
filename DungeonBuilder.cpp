#include "DungeonBuilder.h"
#include "Room.h"

void DungeonBuilder::buildRooms(int maxRooms)
{
	int i;

	location roomPosition = {{-8.0, -8.0}, {8.0, 8.0}};

	Room *room = new Room(roomPosition, 2.0);
	Room::addToList(room);

	for (i = 0; i < maxRooms; i++) {
		int j = 0;
		int roomOffset = rand() % Room::roomList.size();
		std::list<Room*>::iterator it;

		// pick a random room
		for (it = Room::roomList.begin();
		     it != Room::roomList.end() && j <= roomOffset; ++it, ++j);

		it--;

		location _roomPosition;

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
            _roomPosition.ll.x = (*it)->pos.ll.x;
            _roomPosition.ll.y =
                (*it)->pos.tr.y + 2.0f;
            _roomPosition.tr.x = (*it)->pos.tr.x;
            _roomPosition.tr.y =
                (*it)->pos.tr.y + size;
		}
		else if (wall == 1)
		{
			leftDoor = true;
            _roomPosition.ll.x =
                (*it)->pos.tr.x + 2.0f;
            _roomPosition.ll.y = (*it)->pos.ll.y;
            _roomPosition.tr.x =
                (*it)->pos.tr.x + size;
            _roomPosition.tr.y = (*it)->pos.tr.y;
		}
		else if (wall == 2)
		{
			topDoor = true;
            _roomPosition.ll.x = (*it)->pos.ll.x;
            _roomPosition.ll.y =
                (*it)->pos.ll.y - size;
            _roomPosition.tr.x = (*it)->pos.tr.x;
            _roomPosition.tr.y =
                (*it)->pos.ll.y - 2.0f;
		}
		else if (wall == 3)
		{
			rightDoor = true;
            _roomPosition.ll.x =
                (*it)->pos.ll.x - size;
            _roomPosition.ll.y = (*it)->pos.ll.y;
            _roomPosition.tr.x =
                (*it)->pos.ll.x - 2.0f;
            _roomPosition.tr.y = (*it)->pos.tr.y;
		}

		Room *_room = new Room(_roomPosition, 2.0);
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
