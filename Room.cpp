#include "Room.h"

Room::Room(GLfloat lowerLeft[], GLfloat topRight[], GLfloat wallSize)
{
	GLfloat x;

	cout<<"Building room from "<<lowerLeft[0]<<", "<<lowerLeft[1]<<" to "<<
		topRight[0]<<", "<<topRight[1]<<endl;

	// right and left
	for (x = lowerLeft[1]; x <= topRight[1]; x += wallSize)
	{
		// right wall
		GLfloat tmpWallCoords[3] = {topRight[0], x, 0.0};

		Wall *wall = new Wall(tmpWallCoords, wallSize);
		wall->addToList(wall);

		// left wall
		GLfloat tmpWallCoordsLL[3] = {lowerLeft[0], x, 0.0};

		wall = new Wall(tmpWallCoordsLL, wallSize);
		wall->addToList(wall);

	}

	// bottom and top walls
	for (x = lowerLeft[0]; x <= topRight[0]; x += wallSize)
	{
		// bottom wall
		GLfloat tmpWallCoords[3] = {x, lowerLeft[1], 0.0};

		Wall *wall = new Wall(tmpWallCoords, wallSize);
		wall->addToList(wall);

		// top wall
		GLfloat tmpWallCoordsLL[3] = {x, topRight[1], 0.0};

		wall = new Wall(tmpWallCoordsLL, wallSize);
		wall->addToList(wall);
	}
}
