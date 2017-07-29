#include "Player.h"
#include "CyanPotion.h"

CyanPotion::CyanPotion(location _position) :
	   Item(_position)
{
	imageFile = "resources/crawl_tiles/item/potion/cyan.png";
}

bool CyanPotion::checkCollision(Object *obj)
{
	cout<<"Not implemented"<<endl;
	return false;
}

void CyanPotion::onCollisionEnter(Object *obj)
{
	// TODO: If player doesn't pick up potion, they shouldn't collide
	if (obj->tag == "player"
	    && dynamic_cast<Player*>(obj)->getHealth()
	    != dynamic_cast<Player*>(obj)->maxHealth)
	{
		Player *player = dynamic_cast<Player*>(obj);
		std::cout<<player->getHealth()<<std::endl;
		player->addHealth(10);
		std::cout<<player->getHealth()<<std::endl;
		this->destroy();
	}
}

void CyanPotion::destroy()
{
	// only called from Collision.cpp, which already locked ObjectLock
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it != Object::objectList.end(); ++it)
	{
		if ((*it) == this)
		{
			Object::objectList.erase(it);
			delete(*it);
			break;
		}
	}
}
