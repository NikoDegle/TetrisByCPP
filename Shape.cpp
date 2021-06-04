#include "Shape.h"


// 向下移动方法 如果能够向下移动则返回true
bool Shape::moveDown(Background& background) {
	// 从下往上，从左往右循环图形，判断找到的第一个1下方是否有实体 之后break
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = SHAPE_WEIGHT - 1; j >= 0; j--)
		{
			// 检测该格是否为1
			if (body[j][i])
			{
				// 检测背景中该格下方是否有实体
				if (background.content[positionY + j + 1][positionX + i])
				{
					return false;
				}
				break;
			}
		}
	}
	// 全部检查完成后，还没有被阻挡 则往下移动一格
	positionY += 1;
	return true;
}

// 向左移动方法 如果能够移动则移动并返回true
bool Shape::moveLeft(Background& background) {
	// 从左往右 从上往下，检测是否触碰墙壁或者被挡住
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			// 检测该块是否为1
			if (body[i][j])
			{
				// 检测该行左边是否为墙壁 或者有实体
				if ((positionX + j - 1 <= 0) ||
					(background.content[positionY + i][positionX + j - 1]))
				{
					return false;
				}
				break;
			}
		}
	}
	positionX -= 1;
	return true;
}

// 右移方法 如果能够移动返回true
bool Shape::moveRight(Background& background) {
	for (int i = SHAPE_HEIGHT - 1; i >= 0; i--)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			// 检查是否撞墙或者右边有实体
			if (body[j][i])
			{
				if ((positionX + i + 1 >= 20) ||
					(background.content[positionY + j][positionX + i + 1]))
				{
					return false;
				}
				break;
			}
		}
	}
	positionX += 1;
	return true;
}