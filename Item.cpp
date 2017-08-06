#include "stdlib.h"
#include "CyanPotion.h"
#include "MagentaPotion.h"

void randomColor(GLfloat _color[]);

void Item::randomPotion(location _position) {
	int randInt = rand() % 10;
	if (randInt == 0) {
		new MagentaPotion(_position);
	} else {
		new CyanPotion(_position);
	}
}

Item::Item(location _position) : Object(_position)
{
	colliderType = ITEM;
}
