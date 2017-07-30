#include <list>
#include "Wall.h"

class Room
{
public:
	static list<Room*> roomList;

	// coordinates for LL and TR corners
	location position;
	GLfloat lowerLeft[2];
	GLfloat topRight[2];
	GLfloat wallSize;
	//list<Wall*> wallList;

	Room(location, GLfloat);

	static void addToList(Room*);
	void buildRoom();

	bool topDoor = false;
	bool rightDoor = false;
	bool bottomDoor = false;
	bool leftDoor = false;

	bool roomFits = false;

private:
	// Look through roomList, checking if current room will fit (physically)
	// should likely be called by constructor
	bool checkIfFits();
	void addItems();
	void addMaterials();
	location randomLocationInRoom();
};
