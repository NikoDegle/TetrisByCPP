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
class ShapeBugget;
class ShapeLeftSeven;
class ShapeRightSeven;
class ShapeLeftZed;
class ShapeRightZed;
class ShapeSquare;
class ShapeTrangle;

class Background {
public:
	int content[HEIGHT][WEIGHT];	// 游戏盘
	Shape* shapeNow;	// 当前正在操作的图形
	Shape* shapeNext;	// 下一个要操作的图形
	bool gameStatus;	// 当前游戏状态 开始置为true 结束置为false

	Background();
	Background& remove();	// 检查背景中的实体是否有一行为满
	void cleanLine(int& line);	// 从上往下覆盖满的一行
	Background& shapeStop();	// 当前图形停止并转换为背景中的实体
	int** backgroundNow();	// 返回当前背景与运动中的图形样子
	Shape* createNextShape();	// 使用随机数创建下一个形状
	bool getGameStatus();	// 获取当前游戏状态

	// 玩家操作方法
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool changeDirection();
};

#endif // !BACKGROUND_H

