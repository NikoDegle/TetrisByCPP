#include "GameController.h"
#include<iostream>
#include<mutex>
#include<thread>
#include<windows.h>	// Sleep函数
#include<conio.h>	// 无回车读取_getch()函数
using namespace std;

#include "Background.h"

/*
* 初始化游戏控制器方法 需要初始化背景与玩家分数
*/
GameController::GameController() {
	background = nullptr;
	score = 0;
	moveDownTime = 1000;
	m = new mutex;
}

/*
* 析构函数 需要析构背景
*/
GameController::~GameController() {
	if (background)
	{
		delete background;
		background = nullptr;
	}
	if (m)
	{
		delete m;
		m = nullptr;
	}
}

/*
* 返回游戏分数方法
*/
int GameController::getScore() {
	return score;
}

/*
* 返回背景板方法
*/
Background* GameController::getBackground() {
	return background;
}

/*
* 游戏开始方法
*/
bool GameController::gameStart() {
	// 先检查有没有上次游戏残留的背景盘，如果有则删除 并且创建新的游戏背景盘
	if (background)
	{
		delete background;
	}
	background = new Background;
	// 游戏得分置零
	score = 0;
	// 根据方块下落速度设置自动下落计时器线程
	thread moveDownTimer(&GameController::moveDownInTime, this, moveDownTime);
	moveDownTimer.join();
	thread gameMainThread(&GameController::userAction, this);
	gameMainThread.join();
	// 游戏结束后停止线程
	moveDownTimer.~thread();
	gameMainThread.~thread();
	gameEnd();
}

/*
* 自动下落线程方法
*/
void GameController::moveDownInTime(long time) {
	while (background->gameStatus)
	{
		Sleep(time);
		// 如果无法向下移动 则检查游戏是否结束
		if (!safetyMoveDown())
		{
			safetyStatusCheck();
		};
	}
}

/*
* 线程安全的游戏动作操作方法:下移方块
* return 是否成功向下移动方块
*/
bool GameController::safetyMoveDown() {
	m->lock();
	bool result = background->moveDown();
	m->unlock();
	return result;
}

/*
* 线程安全的游戏动作操作方法:左移方块
* return 是否成功向左移动方块
*/
bool GameController::safetyMoveLeft() {
	m->lock();
	bool result = background->moveLeft();
	m->unlock();
	return result;
}

/*
* 线程安全的游戏动作操作方法:右移方块
* return 是否成功向右移动方块
*/
bool GameController::safetyMoveRight() {
	m->lock();
	bool result = background->moveRight();
	m->unlock();
	return result;
}

/*
* 线程安全的游戏动作操作方法:变换当前方块方向
* return 是否成功变换当前方块方向
*/
bool GameController::safetyChangeDirection() {
	m->lock();
	bool result = background->changeDirection();
	m->unlock();
	return result;
}

/*
* 线程安全的检查游戏是否结束方法
*/
void GameController::safetyStatusCheck() {
	m->lock();
	background->shapeStop();
	score += (background->remove()) * 100;
	m->unlock();
}

/*
* 读取用户输入并执行对应操作的方法
*/
void GameController::userAction() {
	// 游戏循环
	while (background->getGameStatus())
	{
		// 读取用户输入
		char ch = getche();
		switch (ch)
		{
		case 'a':
		case 'A': safetyMoveLeft(); break;
		case 'd':
		case 'D': safetyMoveRight(); break;
		case 'j':
		case 'J': safetyChangeDirection(); break;
		case 's':
		case 'S': {
			if (!safetyMoveDown())
			{
				safetyStatusCheck();
			}; 
			break;
		}
		default:
			break;
		}
	}
	// 游戏结束方法
	gameEnd();
}