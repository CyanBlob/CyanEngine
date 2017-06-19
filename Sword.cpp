#include "Sword.h"
#include <chrono>
#include "Collision.h"
#include <unistd.h> // fork()
#include <thread>
#include <sys/wait.h>

list<Sword*> initSwordList()
{
	list<Sword*> tmp;
	return tmp;
}

list <Sword*> Sword::swordList(initSwordList());

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
}

Sword::Sword(GLfloat _lowerLeft[], GLfloat size)
{
	imageFile = "resources/crawl_tiles/spells/air/chain_lightning.png";
	tag = "attack";

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _lowerLeft[0] + size;
	topRight[1] = _lowerLeft[1] + size;


	swordList.push_front(this);
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
	for (std::list<Sword*>::iterator it=Sword::swordList.begin();
	     it != Sword::swordList.end(); ++it)
	{
		if ((*it) == this)
		{
			swordList.erase(it);
			return;
		}
	}
};
