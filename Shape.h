#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#define SHAPE_HEIGHT 4
#define SHAPE_WEIGHT 4

// 不完全数据类型
class Background;

class Shape
{
public:
	int body[SHAPE_HEIGHT][SHAPE_WEIGHT];
	int positionX;	// x轴位置
	int positionY;	// y轴位置
	bool changeDirection(Background& background); // 修改方向
	bool moveLeft(Background& background); // 左移
	bool moveRight(Background& background);	// 右移
	bool moveDown(Background& background);	// 下移
};

#endif // !SHAPE_H


