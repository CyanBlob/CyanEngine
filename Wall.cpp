#include "Wall.h"

using namespace std;

list<Wall*> initWallList()
{
	list<Wall*> tmp;
	return tmp;
}

list <Wall*> Wall::wallList(initWallList());
void randomColor(GLfloat _color[]);

Wall::Wall(GLfloat _coords[][3])
{

	int i, j;

	randomColor(color);

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			coords[i][j] = _coords[i][j];
		}
	}

	//wallList.push_front(this);
}

Wall::Wall(GLfloat lowerLeft[], GLfloat wallSize, GLfloat _color[3])
{

	//randomColor(color);
	color[0] = _color[0];
	color[1] = _color[1];
	color[2] = _color[2];

	coords[0][0] = lowerLeft[0];
	coords[0][1] = lowerLeft[1];
	coords[0][2] = lowerLeft[2];

	coords[1][0] = lowerLeft[0];
	coords[1][1] = lowerLeft[1] + wallSize;
	coords[1][2] = lowerLeft[2];

	coords[2][0] = lowerLeft[0] + wallSize;
	coords[2][1] = lowerLeft[1] + wallSize;
	coords[2][2] = lowerLeft[2];

	coords[3][0] = lowerLeft[0] + wallSize;
	coords[3][1] = lowerLeft[1];
	coords[3][2] = lowerLeft[2];
	//wallList.push_front(this);
}

void Wall::randomColor(GLfloat _color[])
{
	_color[0] = (GLfloat) rand() / RAND_MAX;
	_color[1] = (GLfloat) rand() / RAND_MAX;
	_color[2] = (GLfloat) rand() / RAND_MAX;
}

void Wall::addToList(Wall *wall)
{
	//cout<<"Adding to wallList"<<endl;
	Wall::wallList.push_front(wall);
}
