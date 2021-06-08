#include "ShapeSquare.h"

ShapeSquare::ShapeSquare() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][1] = body[1][2] = body[2][2] = body[2][1] = 1;
	this->positionX = START_X;	// 当该方块出现的时候在从左往右第三格，顶部
	this->positionY = START_Y;
}