#include "Sword.h"
#include <chrono>
#include "Collision.h"
#include <unistd.h> // fork()
#include <sys/wait.h>

list<Sword*> initSwordList()
{
	list<Sword*> tmp;
	return tmp;
}

list <Sword*> Sword::swordList(initSwordList());

Sword::Sword(GLfloat _lowerLeft[], GLfloat size)
{
	imageFile = "resources/crawl_tiles/spells/air/chain_lightning.png";
	tag = "attack";
	int duration = 1;

	lowerLeft[0] = _lowerLeft[0];
	lowerLeft[1] = _lowerLeft[1];
	topRight[0] = _lowerLeft[0] + size;
	topRight[1] = _lowerLeft[1] + size;

	std::chrono::time_point<std::chrono::system_clock> start;
	start = std::chrono::system_clock::now();
	std::time_t startTime = std::chrono::system_clock::to_time_t(start);
	cout<<startTime<<endl;

	swordList.push_front(this);
	Collision::checkPlayerCollision(this);
	this->destroy();
	/*pid_t pid = fork();
	int status;

	if (pid < 0)
	{
		std::cout<<"Fork failed"<<std::endl;
	}
	else if (pid == 0)
	{
		std::cout<<"Child"<<std::endl;
		int i = 0;
		for (; i < 5; i++)
		{
			std::cout<<"Child: "<<i<<std::endl;
		}
	}
	else
	{
		std::cout<<"Parent"<<std::endl;
		int i = 0;
		for (; i < 5; i++)
		{
			std::cout<<"Parent: "<<i<<std::endl;
		}
		//this->destroy();
	}
	return;*/

	/*if (pid == 0)
	{
		//exit(1);
		//return;
	} else if (pid > 0)
	{
		while (wait(&status) != pid)
		{
		}
		std::cout<<"End of loop"<<std::endl;
		this->destroy();
	}*/

	/*while (std::chrono::system_clock::to_time_t(
			std::chrono::system_clock::now()) < startTime + duration)
	{
		std::cout<<"Loop"<<std::endl;
		Collision::checkPlayerCollision(this);
	}*/
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
