#include "ShapeLeftSeven.h"

// 初始化图形7
ShapeLeftSeven::ShapeLeftSeven() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][1] = body[1][2] = body[2][2] = body[3][2] = 1;
	this->positionX = 2;	// 当该方块出现的时候在从左往右第三格，顶部
	this->positionY = 0;
}

// 将方块顺时针旋转90度 将数据存入temp中 检查是否被阻挡
bool ShapeLeftSeven::changeDirection(Background& background) {
	int temp[SHAPE_HEIGHT][SHAPE_WEIGHT] = { 0 };
	// 顺时针旋转
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			temp[j][3 - i] = body[i][j];
		}
	}
	// 检测最左边是否靠墙或者最右边是否靠墙 或者转动后与实体重合
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			if (temp[i][j])
			{
				if (j + positionX <= 0 || j + positionX >= 20)
				{
					return false;
				}
				if (background.content[i + positionY][j + positionX])
				{
					return false;
				}
			}
		}
	}
	// 将形状赋值
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			body[i][j] = temp[i][j];
		}
	}
	return true;
}