#ifndef Included_Material_H
#define Included_Material_H
#include "Material.h"
#endif
#ifndef Included_Crystal_H
#define Included_Crystal_H
#include "Materials/Crystal.h"
#endif
#include "stdlib.h"

void Material::randomMaterial(location _position) {
	int randInt = rand() % 10;
	if (randInt == 0) {
		new Crystal(_position);
	} else {
		new Crystal(_position);
	}
}
