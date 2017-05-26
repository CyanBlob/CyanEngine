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

#include "SOIL.h"

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
Player *player = new Player();

int build = 1;

void buildRooms();

void init(void)
{
	glClearColor(58.0 / 255.0, 60.0 / 255.0, 67 / 255.0, 0.0);
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
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();

	player->render();

	//Translate/rotate
	glTranslatef(xOffset, yOffset, 0);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);

	// render walls
	// TODO: Simplify this (setting up the texture every time is too slow)
	GLuint tex;
	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image =
		    SOIL_load_image("resources/crawl_tiles/dc-dngn/wall/brick_gray0.png"
				    ,&width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		                   GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	for (std::list<Wall*>::iterator it=wall->wallList.begin();
	     it !=wall->wallList.end(); ++it)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); glVertex3f((*it)->lowerLeft[0],
						   (*it)->lowerLeft[1], 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f((*it)->lowerLeft[0],
						   (*it)->topRight[1], 0.0);
		glTexCoord2f(0.0, 0.0); glVertex3f((*it)->topRight[0],
						   (*it)->topRight[1], 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f((*it)->topRight[0],
						   (*it)->lowerLeft[1], 0.0);

		//(*it)->render(); // Too slow, since each call resets image
		glEnd();
	}
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
	int i;
	int MAXROOMS = 500;

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
		/*cout<<j<<", "<<(*it)->lowerLeft[0]<<","<<(*it)->lowerLeft[1]
			<<", "<<(*it)->topRight[0]<<","<<(*it)->topRight[1]
			<<endl;*/

		int _roomLowerLeft[2];
		int _roomTopRight[2];

		int wall = rand() % 4;
		int size = rand() % (20 * 2) + 12;

		bool topDoor = false;
		bool rightDoor = false;
		bool bottomDoor = false;
		bool leftDoor = false;

		if (wall == 0)
		{
			bottomDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0];
			_roomLowerLeft[1] = (*it)->topRight[1] + 2;
			_roomTopRight[0] = (*it)->topRight[0];
			_roomTopRight[1] = (*it)->topRight[1] + size;
		}
		else if (wall == 1)
		{
			leftDoor = true;
			_roomLowerLeft[0] = (*it)->topRight[0] + 2;
			_roomLowerLeft[1] = (*it)->lowerLeft[1];
			_roomTopRight[0] = (*it)->topRight[0] + size;
			_roomTopRight[1] = (*it)->topRight[1];
		}
		else if (wall == 2)
		{
			topDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0];
			_roomLowerLeft[1] = (*it)->lowerLeft[1] - size;
			_roomTopRight[0] = (*it)->topRight[0];
			_roomTopRight[1] = (*it)->lowerLeft[1] - 2;
		}
		else if (wall == 3)
		{
			rightDoor = true;
			_roomLowerLeft[0] = (*it)->lowerLeft[0] - size;
			_roomLowerLeft[1] = (*it)->lowerLeft[1];
			_roomTopRight[0] = (*it)->lowerLeft[0] - 2;
			_roomTopRight[1] = (*it)->topRight[1];
		}

		Room *_room = new Room(_roomLowerLeft, _roomTopRight, 2);
		if (_room->roomFits) {
			if (topDoor) {
				(*it)->bottomDoor = true;
				_room->topDoor = topDoor;
			}
			if (rightDoor) {
				(*it)->leftDoor = true;
				_room->rightDoor = rightDoor;
			}
			if (bottomDoor) {
				_room->bottomDoor = bottomDoor;
				(*it)->topDoor = true;
			}
			if (leftDoor) {
				_room->leftDoor = leftDoor;
				(*it)->rightDoor = true;
			}

			_room->addToList(_room);
		}
	}
	// Build all rooms
	std::list<Room*>::iterator it;
	for (it = Room::roomList.begin(); it != Room::roomList.end(); ++it) {
		(*it)->buildRoom();
		// For debugging/demoing
		//display();
		//usleep(100000);
	}

}

int main(int argc, char** argv)
{
	time_t timeSeed = time(NULL);
	srand(timeSeed);
	cout<<"Running game with seed: "<<timeSeed<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
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
