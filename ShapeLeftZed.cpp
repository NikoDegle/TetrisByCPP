#include "ShapeLeftZed.h"

ShapeLeftZed::ShapeLeftZed() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][0] = body[1][1] = body[2][1] = body[2][2] = 1;
	// 方块出现的位置
	this->positionX = START_X;
	this->positionY = START_Y;
}