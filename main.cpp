#include <stdlib.h>

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <list>
#include <time.h>
#include <boost/chrono.hpp>
#include <boost/thread.hpp> // boost::thread works on Windows
//#include <unistd.h> // sleep()

#include "Player.h"
#include "Room.h"
#include "Sword.h"
#include "DungeonBuilder.h"
#include "Renderer.h"
//#include "Wall.h"

using namespace std;

int maxRooms = 100;
// Stores the status of each key (up/down);
bool keyStates[256] = {false};

static bool left_button_down = false; //Whether the LMB is pressed

Wall *wall;
Player *_player = Player::getPlayer();

int build = 1;

const unsigned int UPDATE_STEP = 15;

unsigned int total_time = 0;
unsigned int current_time = 0;

void buildRooms();

void init(void)
{
	glClearColor(58.0 / 255.0, 60.0 / 255.0, 67 / 255.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_MAP1_VERTEX_3);

	buildRooms();
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
	Renderer::render();
}

void playerAction()
{
	_player->playerAction(keyStates);
}

void timer(int value)
{
	unsigned int new_time = glutGet(GLUT_ELAPSED_TIME);
	unsigned int frame_time = new_time - current_time;
	current_time = new_time;
	total_time += frame_time;

	// perform as many playerAction()s as should have occured while
	// rendering
	while (total_time >= UPDATE_STEP)
	{
		playerAction();
		total_time -= UPDATE_STEP;
	}

	glutPostRedisplay();
	boost::this_thread::sleep_for(boost::chrono::milliseconds(16));
	//TODO: figure out why I need this call, instead of using a while(true)
	glutTimerFunc(0, timer, 1);
}

void menu(int value)
{
	switch(value)
	{
	case 'z':
		Renderer::setZoom(Renderer::getZoom() + 1);
		Renderer::reshape(glutGet(GLUT_WINDOW_WIDTH),
				  glutGet(GLUT_WINDOW_HEIGHT));
		glutPostRedisplay();
		break;
	case 'Z':
		Renderer::setZoom(Renderer::getZoom() - 1);
		Renderer::reshape(glutGet(GLUT_WINDOW_WIDTH),
				  glutGet(GLUT_WINDOW_HEIGHT));
		glutPostRedisplay();
		break;
	case 27:
		for (std::list<Room*>::iterator it=Room::roomList.begin();
		     it !=Room::roomList.end(); ++it) {
			delete(*it);
		}
		Object::objectLock.lock();
		for (std::list<Object*>::iterator it=Object::objectList.begin();
		     it !=Object::objectList.end(); ++it)
		{
			delete(*it);
		}
		Object::objectLock.unlock();
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
	DungeonBuilder::buildRooms(maxRooms);
}

int main(int argc, char** argv)
{
	time_t timeSeed = time(NULL);
	char c;

	while (--argc > 0 && (*++argv)[0] == '-') {
		c = *++argv[0];
		switch (c) {
		case 'n':
			--argc;
			maxRooms = atoi(*++argv);
			break;
		case 's':
			--argc;
			timeSeed = atoi(*++argv);
			break;
		default:
			break;
		}
	}
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
	glutReshapeFunc(Renderer::reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);

	glutMainLoop();

	return 0;
}
