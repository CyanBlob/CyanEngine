#include <list>
#include "Wall.h"

class Room
{
public:
	//static list<Room> roomList;
	// coordinates for LL and TR corners
	int lowerLeft[2];
	int topRight[2];
	list<Wall*> wallList;
	Room(GLfloat*, GLfloat*, GLfloat);

private:
	// Look through roomList, checking if current room will fit (physically)
	// should likely be called by constructor
	bool checkIfFits();
};
