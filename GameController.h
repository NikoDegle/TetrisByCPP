#pragma once

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

class Background;
class Shape;

/*
* 游戏控制器类 用于控制游戏进程
* @author: whc
*/
class GameController
{
public:
	// 初始化
	GameController();
	// 析构
	~GameController();
	// 获取游戏分数方法
	int getScore();
	// 游戏开始方法
	void gameStart();
	// 游戏结束方法
	void gameEnd();
	// 是否再来一次
	bool retry();

	static void print(int** pointer, int height, int weight, bool needDelete);	// 背景输出方法
	static void printShape(Shape& shape);	// 图形输出方法

private:
	// 需要放入游戏背景
	Background* background;
	// 计分板
	int score;
	// 方块自动下落速度
	long moveDownTime;


	// 自动下落计时方法
	void moveDownInTime(long time);
	// 用户动作处理方法
	void userAction();
	// 获取游戏背景方法 该方法需要使用mutex加锁确保多线程安全
	Background* getBackground();
	// 展示游戏画面方法
	void show();
	// 线程安全的游戏动作操作
	bool safetyMoveDown();
	bool safetyMoveRight();
	bool safetyMoveLeft();
	bool safetyChangeDirection();
	void safetyStatusCheck();	// 检查游戏是否结束方法
};

#endif // !GAME_CONTROLLER_H



