#include "ShapeBugget.h"

ShapeBugget::ShapeBugget() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[0][1] = body[1][1] = body[2][1] = body[3][1] = 1;
	// 当该方块出现的时候的位置
	this->positionX = START_X;	
	this->positionY = START_Y - 1;
}