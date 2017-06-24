#include "Sword.h"
#include <chrono>
#include "Collision.h"
#include <unistd.h> // fork()
#include <thread>
#include <sys/wait.h>

void Sword::checkDestroy(Sword *sword)
{
	int duration = 1;
	std::chrono::time_point<std::chrono::system_clock> start;
	start = std::chrono::system_clock::now();
	std::time_t startTime = std::chrono::system_clock::to_time_t(start);

	while (std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()) < startTime + duration)
	{
		Collision::checkPlayerCollision(sword);
	}
	sword->destroy();
	delete sword;
}

Sword::Sword(GLfloat _lowerLeft[], GLfloat size)
{
	imageFile = "resources/crawl_tiles/spells/air/chain_lightning.png";
	tag = "attack";

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _lowerLeft[0] + size;
	topRight[1] = _lowerLeft[1] + size;


	Object::objectList.push_front(this);
	Collision::checkPlayerCollision(this);

	// TODO: find cause of segfault in thread
	std::thread first (checkDestroy, this);
	first.detach();
}

bool Sword::checkCollision(Object *obj)
{
	return false;
}

void Sword::onCollisionEnter(Object *obj)
{
}

void Sword::destroy()
{
	Object::objectLock.lock();
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it != Object::objectList.end(); ++it)
	{
		if ((*it) == this)
		{
			Object::objectList.erase(it);
			break;
		}
	}
	Object::objectLock.unlock();
};
