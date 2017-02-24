#include "Wall.h"

using namespace std;

list<Wall*> initList()
{
	list<Wall*> tmp;
	return tmp;
}

list <Wall*> Wall::wallList(initList());

Wall::Wall(GLfloat _coords[][3])
{

	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			coords[i][j] = _coords[i][j];
		}
	}

	//wallList.push_front(this);
}

void Wall::addToList(Wall *wall)
{
	//cout<<"Adding to wallList"<<endl;
	Wall::wallList.push_front(wall);
}

