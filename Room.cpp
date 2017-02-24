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
		cout<<"Building wall"<<endl;
		GLfloat tmpWallCoords[4][3] = {
			{topRight[0], x, 0.0},
			{topRight[0], x + wallSize, 0.0},
			{topRight[0] + wallSize, x + wallSize, 0.0},
			{topRight[0] + wallSize, x, 0.0}
		};

		Wall *wall = new Wall(tmpWallCoords);
		wall->addToList(wall);
	
		// left wall
		cout<<"Building wall"<<endl;
		GLfloat tmpWallCoordsLeft[4][3] = {
			{lowerLeft[0], x, 0.0},
			{lowerLeft[0], x + wallSize, 0.0},
			{lowerLeft[0] + wallSize, x + wallSize, 0.0},
			{lowerLeft[0] + wallSize, x, 0.0}
		};

		wall = new Wall(tmpWallCoordsLeft);
		wall->addToList(wall);
	
	}

	// bottom and top walls
	for (x = lowerLeft[0]; x <= topRight[0]; x += wallSize)
	{
		// bottom wall
		cout<<"Building wall"<<endl;
		GLfloat tmpWallCoords[4][3] = {
			{x, lowerLeft[1], 0.0},
			{x, lowerLeft[1] + wallSize, 0.0},
			{x + wallSize, lowerLeft[1] + wallSize, 0.0},
			{x + wallSize, lowerLeft[1], 0.0}
		};

		Wall *wall = new Wall(tmpWallCoords);
		wall->addToList(wall);
	
		// top wall
		cout<<"Building wall"<<endl;
		GLfloat tmpWallCoordsTop[4][3] = {
			{x, topRight[1], 0.0},
			{x, topRight[1] + wallSize, 0.0},
			{x + wallSize, topRight[1] + wallSize, 0.0},
			{x + wallSize, topRight[1], 0.0}
		};

		wall = new Wall(tmpWallCoordsTop);
		wall->addToList(wall);
	
	}
}
