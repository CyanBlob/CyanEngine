#include "Object.h"
#include "SOIL.h"
#include <iostream>

GLuint tex;
float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
int width, height;
unsigned char* image;

void Object::initRender()
{glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// background color, for transparent backgrounds
	glColor3f(58.0 / 255.0, 60.0 / 255.0, 67 / 255.0);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glGenerateMipMap(GL_TEXTURE_2D);

	image = SOIL_load_image(imageFile, &width, &height,
				0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		     GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}
void Object::render()
{

	//glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(lowerLeft[0], lowerLeft[1], 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(lowerLeft[0], topRight[1], 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(topRight[0], topRight[1], 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(topRight[0], lowerLeft[1], 0.0);

	glEnd();
}
