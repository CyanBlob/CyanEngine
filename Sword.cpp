#include "Sword.h"
#include <chrono>
#include "Collision.h"
#include <unistd.h> // fork()
#include <thread>
#include <sys/wait.h>

void Sword::checkDestroy(Sword *sword)
{
	int duration = 500000000;
	long startTime =
		std::chrono::system_clock::now().time_since_epoch().count();

	while (std::chrono::system_clock::now().time_since_epoch().count()
	       < startTime + duration)
	{
		Collision::checkPlayerCollision(sword);
		usleep(1000);
	}
	sword->destroy();
	delete sword;
}

Sword::Sword(GLfloat _lowerLeft[], GLfloat size)
{
	imageFile = "resources/crawl_tiles/spells/air/chain_lightning.png";
	tag = "attack";
	colliderType = PLAYER_ATTACK;
	collidesWith = ENVIRONMENT | ENEMY;

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _lowerLeft[0] + size;
	topRight[1] = _lowerLeft[1] + size;


	Object::objectLock.lock();
	Object::objectList.push_front(this);
	Object::objectLock.unlock();
	Collision::checkPlayerCollision(this);

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
