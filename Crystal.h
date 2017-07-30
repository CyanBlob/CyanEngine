#ifndef Included_Material_H
#define Included_Material_H
#include "Material.h"
#endif

using namespace std;

class Crystal: public Material
{
public:
	Crystal(location);
	~Crystal(){};
};
