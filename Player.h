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

static Object* thisRef = nullptr;

class Player: public Object
{
public:
	GLfloat xOffset;
	GLfloat yOffset;

	int maxHealth = 100;
	int heading = 0;

	GLfloat color[3] = {0.0, 1.0, 1.0};
	GLfloat flashColor[3] = {1.0, 0.0, 0.0};
	// Rect coordinates
	GLfloat mainRect[4][3];

	void playerAction(bool*);
	void copyGLfloatArray(GLfloat*, GLfloat*);
	void onCollisionEnter(Object*);
	void addHealth(int);
	int getHealth();
	void addStr(int);
	int getStr();
	static Player* getPlayer();

private:
	Player();
	GLfloat speedForward;
	GLfloat speedBack;
	GLfloat speedLeft;
	GLfloat speedRight;
	int health = 50;
	int strength = 0;
	bool playerAttacking = false;
	long attackTime = 0;
	int attackDelay = 500000000;
	void attack();
	void stopAttack();
	bool playerCollision(location, GLfloat, GLfloat);
};
