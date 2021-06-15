#include "GameController.h"
#include<iostream>
#include<mutex>
#include<thread>
#include<windows.h>	// Sleep函数
#include<conio.h>	// 无回车读取_getch()函数
using namespace std;

#include "Background.h"
#include "Shape.h"

// 线程锁
mutex m;

/*
* 初始化游戏控制器方法 需要初始化背景与玩家分数
*/
GameController::GameController() {
	background = new Background;
	score = 0;
	moveDownTime = 1000;
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
void GameController::gameStart() {
	// 是否重复标识符
	bool flag = false;
	do
	{
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
		thread gameMainThread(&GameController::userAction, this);
		gameMainThread.join();
		moveDownTimer.join();
		// 游戏结束后停止线程
		moveDownTimer.~thread();
		gameMainThread.~thread();
		gameEnd();
		
		// 是否再来一次
		flag = retry();
	} while (flag);
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
	m.lock();
	bool result = background->moveDown();
	// 操作完成后展示画面
	show();
	m.unlock();
	return result;
}

/*
* 线程安全的游戏动作操作方法:左移方块
* return 是否成功向左移动方块
*/
bool GameController::safetyMoveLeft() {
	m.lock();
	bool result = background->moveLeft();
	// 操作完成后展示画面
	show();
	m.unlock();
	return result;
}

/*
* 线程安全的游戏动作操作方法:右移方块
* return 是否成功向右移动方块
*/
bool GameController::safetyMoveRight() {
	m.lock();
	bool result = background->moveRight();
	// 操作完成后展示画面
	show();
	m.unlock();
	return result;
}

/*
* 线程安全的游戏动作操作方法:变换当前方块方向
* return 是否成功变换当前方块方向
*/
bool GameController::safetyChangeDirection() {
	m.lock();
	bool result = background->changeDirection();
	// 操作完成后展示画面
	show();
	m.unlock();
	return result;
}

/*
* 线程安全的检查游戏是否结束方法
*/
void GameController::safetyStatusCheck() {
	m.lock();
	background->shapeStop();
	score += (background->remove()) * 100;
	m.unlock();
}

/*
* 读取用户输入并执行对应操作的方法
*/
void GameController::userAction() {
	// 游戏循环
	while (background->getGameStatus())
	{
		// 读取用户输入
		char ch = _getche();
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
}

/*
* 游戏结束方法 游戏结束后输出得分与游戏结束字样
* return 游戏是否成功结束
*/
void GameController::gameEnd() {
	system("cls");
	cout << "游戏结束，最终得分:" << score << endl;
}

/*
* 是否再来一次方法
* return 是否再来一次
*/
bool GameController::retry() {
	char ch;
	// 清除之前的输入
	cin.clear();
	cin.sync();
	cout << "再来一次请输入y,否则输入任意字符" << endl;
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
	{
		return true;
	}
	return false;
}

/*
* 展示游戏当前画面方法
*/
void GameController::show() {
	system("cls");
	print(background->backgroundNow(), HEIGHT, WEIGHT, true);
	cout << "next:" << endl;
	if (background->shapeNext)
	{
		printShape(*background->shapeNext);
	}
}

/*
* 输出整个游戏画面方法
*/
void GameController::print(int** pointer, int height, int weight, bool needDelete) {
	// 输出顶部框
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		// 每行开始
		cout << "|";
		for (int j = 0; j < weight; j++) {
			if (pointer[i][j])
			{
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << "|" << endl;
	}
	// 输出底部框
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl << endl;
	// 如果需要释放
	if (needDelete)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] pointer[i];
		}
		delete[] pointer;
	}
}

// 输出形状当前状态
void GameController::printShape(Shape& shape) {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			if (shape.body[i][j])
			{
				cout << "*";
			}
			else {
				cout << "+";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}