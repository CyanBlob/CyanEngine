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
#include <string>

#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

class Player: public Object
{
public:
	GLfloat xOffset;
	GLfloat yOffset;

	GLfloat color[3] = {0.0, 1.0, 1.0};
	GLfloat flashColor[3] = {1.0, 0.0, 0.0};
	// Rect coordinates
	GLfloat mainRect[4][3];

	void playerAction(bool*);
	void copyGLfloatArray(GLfloat*, GLfloat*);
	void onCollisionEnter(Object*);
	Player();

private:
	GLfloat speedForward;
	GLfloat speedBack;
	GLfloat speedLeft;
	GLfloat speedRight;
	bool playerAttacking = false;
	void attack();
	void stopAttack();
	bool playerCollision(GLfloat[][3], GLfloat, GLfloat);
};
