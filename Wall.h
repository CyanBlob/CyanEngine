#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glut.h>

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <list>

using namespace std;

class Wall
{
public:
	GLfloat coords[4][3];
	GLfloat color[3];

	static list<Wall*> wallList;
	bool colliderEnabled;

	// Pass in all 4 coordinates
	Wall(GLfloat[][3]);

	// Pass in LL coordinate + size of wall
	Wall(GLfloat[3], GLfloat wallSize);

	void addToList(Wall*);

	//void randomColor(GLfloat[]);
private:
};
