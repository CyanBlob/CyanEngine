#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <list>

#include "Object.h"

using namespace std;

class Wall: public Object
{
public:
	~Wall() {};
	GLfloat coords[4][3];
	GLfloat color[3];

	static list<Wall*> wallList;
	bool colliderEnabled;

	// Pass in all 4 coordinates
	Wall(GLfloat[][3]);

	// Pass in LL coordinate + size of wall
	Wall(GLfloat[3], GLfloat wallSize, GLfloat[3]);

	void addToList(Wall*);

	static void randomColor(GLfloat[]);
	bool checkCollision(Object*);
	void onCollisionEnter(Object*);
	//void destroy();
private:
};
