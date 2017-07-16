#include "Player.h"
#include "MagentaPotion.h"

MagentaPotion::MagentaPotion(GLfloat _lowerLeft[2], GLfloat _topRight[2]) :
	   Item(_lowerLeft, _topRight)
{
	imageFile = "resources/crawl_tiles/item/potion/magenta.png";
}

bool MagentaPotion::checkCollision(Object *obj)
{
	cout<<"Not implemented"<<endl;
	return false;
}

void MagentaPotion::onCollisionEnter(Object *obj)
{
	// TODO: If player doesn't pick up potion, they shouldn't collide
	if (obj->tag == "player")
	{
		Player *player = dynamic_cast<Player*>(obj);
		std::cout<<player->getStr()<<std::endl;
		player->addStr(1);
		std::cout<<player->getStr()<<std::endl;
		this->destroy();
	}
}

void MagentaPotion::destroy()
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
