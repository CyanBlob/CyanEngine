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
#include <unistd.h> // sleep()

#include "Player.h"
#include "Room.h"
//#include "Wall.h"

using namespace std;

// Stores the status of each key (up/down);
bool* keyStates = new bool[256];

static float zoom = 180; //Zoom level
static bool left_button_down = false; //Whether the LMB is pressed

//Translation variables
GLfloat xOffset = 0.0;
GLfloat yOffset = 0.0;

//Rotaion variables
static float xRot = 0;
static float yRot = 0;

list<Wall*> wallList;
Wall *wall;
Player player;

int build = 1;

void buildRooms();

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);
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

void display(void)
{
	int i;

	glPushMatrix();

	//Translate/rotate
	glTranslatef(xOffset, yOffset, 0);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(player.color[0], player.color[1], player.color[2]);
	glBegin(GL_POLYGON);
	for (i = 0; i < (int) (sizeof player.mainRect
			       / sizeof player.mainRect[0]); i++)
	{
		glVertex3fv(&player.mainRect[i][0]);
	}

	glEnd();

	// TODO: Research C++ iterators
	for (std::list<Wall*>::iterator it=wall->wallList.begin();
	     it !=wall->wallList.end(); ++it)
	{
	glColor3f((*it)->color[0],(*it)->color[1],(*it)->color[2]);
	glBegin(GL_POLYGON);
		for (i = 0; i < (int) (sizeof (*it)->coords
				       / sizeof (*it)->coords[0]); i++)
		{
			glVertex3fv(&(*it)->coords[i][0]);
		}
	glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();

}

void playerAction()
{
	player.playerAction(keyStates);
	xOffset = player.xOffset;
	yOffset = player.yOffset;
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
	int i;
	int MAXROOMS = 50;

	int roomLowerLeft[2] = {-8, -8};
	int roomTopRight[2] = {8, 8};

	Room *room = new Room(roomLowerLeft, roomTopRight, 2);
	room->addToList(room);

	for (i = 0; i < MAXROOMS; i++) {
		int j = 0;
		int roomOffset = rand() % Room::roomList.size();
		std::list<Room*>::iterator it;

		// pick a random room
		for (it = Room::roomList.begin();
		     it != Room::roomList.end() && j <= roomOffset; ++it, ++j);

		it--;
		cout<<j<<", "<<(*it)->lowerLeft[0]<<","<<(*it)->lowerLeft[1]
			<<", "<<(*it)->topRight[0]<<","<<(*it)->topRight[1]
			<<endl;

		int _roomLowerLeft[2];
		int _roomTopRight[2];

		int wall = rand() % 4;
		int size = rand() % 20 * 2 + 10;

		bool topDoor = false;
		bool rightDoor = false;
		bool bottomDoor = false;
		bool leftDoor = false;

		if (wall == 0)
		{
			(*it)->topDoor = true;
			bottomDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0];
			_roomLowerLeft[1] = (*it)->topRight[1] + 2;
			_roomTopRight[0] = (*it)->topRight[0];
			_roomTopRight[1] = (*it)->topRight[1] + size;
		}
		else if (wall == 1)
		{
			(*it)->rightDoor = true;
			leftDoor = true;
			_roomLowerLeft[0] = (*it)->topRight[0] + 2;
			_roomLowerLeft[1] = (*it)->lowerLeft[1];
			_roomTopRight[0] = (*it)->topRight[0] + size;
			_roomTopRight[1] = (*it)->topRight[1];
		}
		else if (wall == 2)
		{
			(*it)->bottomDoor = true;
			topDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0];
			_roomLowerLeft[1] = (*it)->lowerLeft[1] - size;
			_roomTopRight[0] = (*it)->topRight[0];
			_roomTopRight[1] = (*it)->lowerLeft[1] - 2;
		}
		else if (wall == 3)
		{
			(*it)->leftDoor = true;
			rightDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0] - size;
			_roomLowerLeft[1] = (*it)->lowerLeft[1];
			_roomTopRight[0] = (*it)->lowerLeft[0] - 2;
			_roomTopRight[1] = (*it)->topRight[1];
		}

		Room *_room = new Room(_roomLowerLeft, _roomTopRight, 2);
		_room->topDoor = topDoor;
		_room->rightDoor = rightDoor;
		_room->bottomDoor = bottomDoor;
		_room->leftDoor = leftDoor;
		_room->addToList(_room);
	}
	// Build all rooms
	std::list<Room*>::iterator it;
	for (it = Room::roomList.begin(); it != Room::roomList.end(); ++it) {
		(*it)->buildRoom();
	}

}

int main(int argc, char** argv)
{
	time_t timeSeed = time(NULL);
	srand(timeSeed);
	cout<<"Running game with seed: "<<timeSeed<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1000, 1000);
	//glutInitWindowPosition (100, 100);
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
