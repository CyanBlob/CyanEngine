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
#include <time.h>
//#include <unistd.h> // sleep()

#include "Player.h"
#include "Room.h"
#include "CyanPotion.h"
#include "Sword.h"
#include "DungeonBuilder.h"
//#include "Wall.h"

#include "SOIL.h"

#define MAXROOMS 100

using namespace std;

// Stores the status of each key (up/down);
bool keyStates[256] = {false};

static float zoom = 35; //Zoom level
static bool left_button_down = false; //Whether the LMB is pressed

//Translation variables
GLfloat xOffset = 0.0;
GLfloat yOffset = 0.0;

//Rotaion variables
static float xRot = 0;
static float yRot = 0;

Wall *wall;
Player *player = new Player();
CyanPotion *testItem;

int build = 1;

GLuint floorTex;
bool floorTexSet = false;

void buildRooms();

void init(void)
{
	glClearColor(58.0 / 255.0, 60.0 / 255.0, 67 / 255.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);

	// Test items
	GLfloat tmpLL[2] = {3, 3};
	GLfloat tmpTR[2] = {5, 5};
	testItem = new CyanPotion(tmpLL, tmpTR);
}

//Check which mouse button was pressed
void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		left_button_down = true;
	}
	else
	{
		left_button_down = false;
	}
}

//Reset cursor
void passiveMouseMotion(int x, int y)
{
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glutPostRedisplay();
}

void mouseMotion(int x,int y)
{
}

// TODO: create floor object
void renderFloor()
{
	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	int width, height;
	//unsigned char* image;
	const char* imageFile = "resources/custom/floor_400.png";
	unsigned char* image;
	GLfloat lowerLeft[2] = {-400, -400};
	GLfloat topRight[2] = {400, 400};

	// prevent loading the floor texture every frame (it can be huge)
	if (!floorTexSet) {
		floorTexSet = 1;

		glGenTextures(1, &floorTex);

		glBindTexture(GL_TEXTURE_2D, floorTex);

		// generate mipmaps
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST_MIPMAP_NEAREST);

		image = SOIL_load_image(imageFile, &width, &height,
					     0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			     GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);
	} else {
		glBindTexture(GL_TEXTURE_2D, floorTex);
	}

	//glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(lowerLeft[0], lowerLeft[1], 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(lowerLeft[0], topRight[1], 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(topRight[0], topRight[1], 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(topRight[0], lowerLeft[1], 0.0);
	glEnd();

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	//Translate/rotate
	glTranslatef(xOffset, yOffset, 0);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);

	renderFloor();

	const char *prevImage = 0;
	// TODO: Generalize this
	// render walls
	Object::objectLock.lock();
	for (std::list<Object*>::iterator it=Object::objectList.begin();
	     it !=Object::objectList.end(); ++it)
	{
		if ((*it)->imageFile != prevImage)
		{
			(*it)->initRender();
			prevImage = (*it)->imageFile;
		}
		(*it)->render();
	}
	Object::objectLock.unlock();

	//glTranslatef(xOffset * -1, yOffset * -1, 0);
	player->initRender();
	player->render();
	glFlush();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glutSwapBuffers();
}

void playerAction()
{
	player->playerAction(keyStates);
	xOffset = player->xOffset;
	yOffset = player->yOffset;
}

void timer(int value)
{
	if (build == 1)
	{
		buildRooms();
		build = 0;
	}

	playerAction();
	glutPostRedisplay();
	glutTimerFunc(16, timer, 1);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-zoom, zoom, -zoom*(GLfloat)h/(GLfloat)w,
			zoom*(GLfloat)h/(GLfloat)w, -25.0, 25.0);
	else
		glOrtho(-zoom*(GLfloat)w/(GLfloat)h,
			zoom*(GLfloat)w/(GLfloat)h, -zoom, zoom, -25.0, 25.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menu(int value)
{
	switch(value)
	{
	case 'z':
		zoom++;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glutPostRedisplay();
		break;
	case 'Z':
		zoom--;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glutPostRedisplay();
		break;
	case 'x':
		xRot += 2;
		if(xRot > 90)
			xRot = 90;
		glutPostRedisplay();
		break;
	case 'X':
		xRot -= 2;
		if(xRot < 0)
			xRot = 0;
		glutPostRedisplay();
		break;
	case 'y':
		yRot += 2;
		if(yRot > 90)
			yRot = 90;
		glutPostRedisplay();
		break;
	case 'Y':
		yRot -= 2;
		if(yRot < 0)
			yRot = 0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}

void createMenu(void)
{
	glutCreateMenu(menu);

	glutAddMenuEntry("z: Zoom out", 'z');
	glutAddMenuEntry("Z: Zoom in", 'Z');
	glutAddMenuEntry("x: Rotate x", 'x');
	glutAddMenuEntry("X: Rotate x", 'X');
	glutAddMenuEntry("y: Rotate y", 'y');
	glutAddMenuEntry("Y: Rotate y", 'Y');
	glutAddMenuEntry("w: Pan up", 'w');
	glutAddMenuEntry("s: Pan down", 's');
	glutAddMenuEntry("a: Pan left", 'a');
	glutAddMenuEntry("d: Pan right", 'd');
	glutAddMenuEntry("esc: Quit", 27);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboardUp(unsigned char key, int x, int y)
{
	menu(key);
	keyStates[key] = false;

}
void keyboard(unsigned char key, int x, int y)
{
	menu(key);
	keyStates[key] = true;
}

//TODO: Don't add rooms to roomList if they didn't fit
void buildRooms()
{
	DungeonBuilder::buildRooms(MAXROOMS);
}

int main(int argc, char** argv)
{
	time_t timeSeed = time(NULL);
	srand(timeSeed);
	cout<<"Running game with seed: "<<timeSeed<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowSize (1000, 1000);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	createMenu();
	init ();
	glutDisplayFunc(display);
	glutTimerFunc(16, timer, 1);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);

	glutMainLoop();

	return 0;
}
