#include <list>

class Room
{
public:
	//static list<Room> roomList;
	// coordinates for LL and TR corners
	int lowerLeft[2];
	int topRight[2];


private:
	Room(int*, int*);
	// Look through roomList, checking if current room will fit (physically)
	// should likely be called by constructor
	bool checkIfFits();
};
