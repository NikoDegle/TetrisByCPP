#include "ShapeLeftSeven.h"
#include "Background.h"

// 初始化图形7
ShapeLeftSeven::ShapeLeftSeven() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][1] = body[1][2] = body[2][2] = body[3][2] = 1;
	this->positionX = 4;	// 当该方块出现的时候在从左往右第三格，顶部
	this->positionY = -1;
}