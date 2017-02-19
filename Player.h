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

class Player
{
public:
	GLfloat speedForward;
	GLfloat speedBack;
	GLfloat speedLeft;
	GLfloat speedRight;

	GLfloat xOffset;
	GLfloat yOffset;

	// Rect coordinates
	GLfloat mainRect[4][3];

	void playerAction(bool*);
	Player();
};
