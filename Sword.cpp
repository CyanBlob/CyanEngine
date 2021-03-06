#include "Sword.h"
#include <chrono>
#include "Collision.h"
#include <unistd.h> // fork()
#include <boost/chrono.hpp>
#include <boost/thread.hpp> // boost::thread works on Windows
#include <sys/wait.h>

void Sword::checkDestroy(Sword *sword)
{
	int duration = 500000000;
	long startTime =
		std::chrono::system_clock::now().time_since_epoch().count();

	while (std::chrono::system_clock::now().time_since_epoch().count()
	       < startTime + duration)
	{
		Collision::checkCollision(sword);
		boost::this_thread::sleep_for(
				      boost::chrono::microseconds(1000));
	}
	sword->destroy();
	delete sword;
}

Sword::Sword(location _position) : Object(_position)
{
	imageFile = "resources/crawl_tiles/spells/air/chain_lightning.png";
	tag = "attack";
	colliderType = PLAYER_ATTACK;
	collidesWith = ENVIRONMENT | ENEMY;

	Collision::checkCollision(this);

	boost::thread first (checkDestroy, this);
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
