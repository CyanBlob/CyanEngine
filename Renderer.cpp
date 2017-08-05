#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glut.h>
#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

#include "Renderer.h"
#include "SOIL.h"
#include "Player.h"

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

//Translation variables
GLfloat xOffset = 0.0;
GLfloat yOffset = 0.0;

//Rotaion variables
static float xRot = 0;
static float yRot = 0;


GLuint floorTex;
bool floorTexSet = false;

Player* player = Player::getPlayer();

int Renderer::zoom = 35;

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

		// TODO: Test if filtering is working
		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
				fLargest);

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

void Renderer::render()
{
	xOffset = player->xOffset;
	yOffset = player->yOffset;

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

	// simulate laggy rendering
	//boost::this_thread::sleep_for(boost::chrono::milliseconds(50));

	glPopMatrix();
	glutSwapBuffers();
}

void Renderer::setZoom(int _zoom)
{
	zoom = _zoom;
}

int Renderer::getZoom()
{
	return zoom;
}

void Renderer::reshape(int w, int h)
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
