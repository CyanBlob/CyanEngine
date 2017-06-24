#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <list>

#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif
#include "SOIL.h"

using namespace std;

class Wall: public Object
{
public:
	~Wall() {};
	GLfloat coords[4][3];
	GLfloat color[3];

	bool colliderEnabled;

	// Pass in all 4 coordinates
	Wall(GLfloat[][3]);

	// Pass in LL coordinate + size of wall
	Wall(GLfloat[3], GLfloat wallSize, GLfloat[3]);

	void addToList(Wall*);

	static void randomColor(GLfloat[]);
	bool checkCollision(Object*);
	void onCollisionEnter(Object*);

	static bool lessThan(Wall *A, Wall *B)
	{
		return A->imageFile < B->imageFile;
	}
	void destroy();
};
