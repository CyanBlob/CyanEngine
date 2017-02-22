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
	GLfloat color[3] = {0.3, 0.3, 0.3};

	bool colliderEnabled;
	Wall(GLfloat[][3]);
	static list<Wall*> wallList;

	void addToList(Wall*);
private:
};
