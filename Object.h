#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glut.h>
#include <string>
#include <mutex>
#include <list>

class Object
{
public:

	Object();
	~Object() {};
	static std::mutex objectLock;
	static std::list<Object*> objectList;

	std::string tag = "object";
	GLfloat lowerLeft[2];
	GLfloat topRight[2];

	bool colliderEnabled;
	bool checkCollision(Object*);

	void initRender();
	void render();

	virtual void onCollisionEnter(Object*) = 0;
	const char *imageFile;

	static bool lessThan(Object *A, Object *B)
	{
		return A->imageFile < B->imageFile;
	}
	//virtual void destroy();
};
