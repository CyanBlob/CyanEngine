#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif
#include "SOIL.h"
#include <iostream>

GLuint tex;
float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
int width, height;
unsigned char* image;

std::mutex Object::objectLock;

std::list<Object*> initObjectList()
{
	std::list<Object*> tmp;
	return tmp;
}

std::list <Object*> Object::objectList(initObjectList());

Object::Object()
{
}

void Object::initRender()
{
	// TODO: Figure out why this causes a memory leak,
	// and why things work without it
	//glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);

	// generate mipmaps
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// TODO: Test if filtering is working
	GLfloat fLargest;
	//glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			GL_NEAREST_MIPMAP_NEAREST);

	//glGenerateMipMap(GL_TEXTURE_2D);

	image = SOIL_load_image(imageFile, &width, &height,
				0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		     GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	// I'm not 100% what this call does, but it breaks transparency
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}

void Object::render()
{

	//glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(position.lowerLeft.x,
					   position.lowerLeft.y, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(position.lowerLeft.x,
					   position.topRight.y, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(position.topRight.x,
					   position.topRight.y, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(position.topRight.x,
					   position.lowerLeft.y, 0.0);

	glEnd();
}
