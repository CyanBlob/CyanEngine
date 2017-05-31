#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glut.h>
#include <string>

class Object
{
public:

	Object() {};
	~Object() {};

	std::string tag = "object";
	GLfloat lowerLeft[2];
	GLfloat topRight[2];

	bool colliderEnabled;
	bool checkCollision(Object*);

	void initRender();
	void render();

	virtual void onCollisionEnter(Object*) = 0;
	const char *imageFile;
	//virtual void destroy();
};
