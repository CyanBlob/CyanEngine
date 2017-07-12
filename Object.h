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

#define PLAYER 1
#define PLAYER_ATTACK 2
#define ENEMY 4
#define ENEMY_ATTACK 8
#define ENVIRONMENT 16
#define ITEM 32


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

	int colliderType = 0;
	int collidesWith = 0;

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
