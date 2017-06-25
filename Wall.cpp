#include "Wall.h"

using namespace std;

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
}

Wall::Wall(GLfloat _lowerLeft[], GLfloat wallSize, GLfloat _color[3])
{
	tag = "wall";

	int i = rand() % 4;
	if (i == 0)
	{
		imageFile = "resources/crawl_tiles/dc-dngn/wall/stone2_dark0.png";
	}
	else if (i == 1)
	{
		imageFile = "resources/crawl_tiles/dc-dngn/wall/stone2_dark1.png";
	}
	else if (i == 2)
	{
		imageFile = "resources/crawl_tiles/dc-dngn/wall/stone2_dark2.png";
	}
	else if (i == 3)
	{
		imageFile = "resources/crawl_tiles/dc-dngn/wall/stone2_dark3.png";
	}

	//randomColor(color);
	color[0] = _color[0];
	color[1] = _color[1];
	color[2] = _color[2];

	coords[0][0] = _lowerLeft[0];
	coords[0][1] = _lowerLeft[1];
	coords[0][2] = _lowerLeft[2];

	coords[1][0] = _lowerLeft[0];
	coords[1][1] = _lowerLeft[1] + wallSize;
	coords[1][2] = _lowerLeft[2];

	coords[2][0] = _lowerLeft[0] + wallSize;
	coords[2][1] = _lowerLeft[1] + wallSize;
	coords[2][2] = _lowerLeft[2];

	coords[3][0] = _lowerLeft[0] + wallSize;
	coords[3][1] = _lowerLeft[1];
	coords[3][2] = _lowerLeft[2];
	//wallList.push_front(this);

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];

	topRight[0] = _lowerLeft[0] + wallSize;
	topRight[1] = _lowerLeft[1] + wallSize;
}

void Wall::randomColor(GLfloat _color[])
{
	_color[0] = (GLfloat) rand() / RAND_MAX;
	_color[1] = (GLfloat) rand() / RAND_MAX;
	_color[2] = (GLfloat) rand() / RAND_MAX;
}

void Wall::addToList(Wall *wall)
{
	Object::objectList.push_front(this);
}

bool Wall::checkCollision(Object *obj)
{
	cout<<"Not implemented"<<endl;
	return false;
}

void Wall::onCollisionEnter(Object *obj)
{
	if (obj->tag == "attack")
	{
		this->destroy();
	}
}

void Wall::destroy()
{
	//Object::objectLock.lock();
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it != Object::objectList.end(); ++it)
	{
		if ((*it) == this)
		{
			Object::objectList.erase(it);
			break;
		}
	}
	//Object::objectLock.unlock();
};
