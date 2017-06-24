#include <list>
#ifndef Included_Object_H
#define Included_Object_H
#include "Object.h"
#endif

using namespace std;

class Sword: public Object
{
public:
	Sword(GLfloat[2], GLfloat);
	~Sword() {};

	static std::mutex swordLock;
	bool colliderEnabled;

	bool checkCollision(Object*);
	void onCollisionEnter(Object*);

	static void checkDestroy(Sword*);
	void destroy();
};
