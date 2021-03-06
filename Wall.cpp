#include "Wall.h"

using namespace std;

void randomColor(GLfloat _color[]);

Wall::Wall(location _position) : Object(_position)
{
	tag = "wall";
	colliderType = ENVIRONMENT;

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
}

void Wall::randomColor(GLfloat _color[])
{
	_color[0] = (GLfloat) rand() / RAND_MAX;
	_color[1] = (GLfloat) rand() / RAND_MAX;
	_color[2] = (GLfloat) rand() / RAND_MAX;
}

void Wall::addToList(Wall *wall)
{
	//Object::objectList.push_front(this);
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
