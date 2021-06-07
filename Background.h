#pragma once

#ifndef BACKGROUND_H
#define BACKGROUND_H

/*
	俄罗斯方块整体背景
*/
#define HEIGHT 10
#define WEIGHT 20

// 不完全数据类型
class Shape;

class Background {
public:
	int content[HEIGHT][WEIGHT];	// 游戏盘
	Shape* shapeNow;	// 当前正在操作的图形
	Shape* shapeNext;	// 下一个要操作的图形

	Background();
	void remove();
	void cleanLine(int& line);
	void shapeStop();	// 当前图形停止并转换为背景中的实体
	int** backgroundNow();	// 返回当前背景与运动中的图形样子

	// 玩家操作方法
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool changeDirection();
};

#endif // !BACKGROUND_H

