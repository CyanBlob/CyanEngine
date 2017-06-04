#include "Player.h"
#include "CyanPotion.h"

CyanPotion::CyanPotion(GLfloat _lowerLeft[2], GLfloat _topRight[2]) :
	   Item(_lowerLeft, _topRight)
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
	std::cout<<obj->tag<<std::endl;
	if (obj->tag == "player")
	{
		Player *player = dynamic_cast<Player*>(obj);
		std::cout<<player->health<<std::endl;
		player->health += 10;
		std::cout<<player->health<<std::endl;
		this->destroy();
	}
}

void CyanPotion::destroy()
{
	for (std::list<Item*>::iterator it=Item::itemList.begin();
	     it != Item::itemList.end(); ++it)
	{
		if ((*it) == this)
		{
			itemList.erase(it);
			return;
		}
	}
}
