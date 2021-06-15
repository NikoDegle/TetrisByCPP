#include "GameController.h"
#include<iostream>
#include<mutex>
#include<thread>
#include<windows.h>	// Sleep����
#include<conio.h>	// �޻س���ȡ_getch()����
using namespace std;

#include "Background.h"
#include "Shape.h"

// �߳���
mutex m;

/*
* ��ʼ����Ϸ���������� ��Ҫ��ʼ����������ҷ���
*/
GameController::GameController() {
	background = new Background;
	score = 0;
	moveDownTime = 1000;
}

/*
* �������� ��Ҫ��������
*/
GameController::~GameController() {
	if (background)
	{
		delete background;
		background = nullptr;
	}
}

/*
* ������Ϸ��������
*/
int GameController::getScore() {
	return score;
}

/*
* ���ر����巽��
*/
Background* GameController::getBackground() {
	return background;
}

/*
* ��Ϸ��ʼ����
*/
void GameController::gameStart() {
	// �Ƿ��ظ���ʶ��
	bool flag = false;
	do
	{
		// �ȼ����û���ϴ���Ϸ�����ı����̣��������ɾ�� ���Ҵ����µ���Ϸ������
		if (background)
		{
			delete background;
		}
		background = new Background;
		// ��Ϸ�÷�����
		score = 0;
		// ���ݷ��������ٶ������Զ������ʱ���߳�
		thread moveDownTimer(&GameController::moveDownInTime, this, moveDownTime);
		thread gameMainThread(&GameController::userAction, this);
		gameMainThread.join();
		moveDownTimer.join();
		// ��Ϸ������ֹͣ�߳�
		moveDownTimer.~thread();
		gameMainThread.~thread();
		gameEnd();
		
		// �Ƿ�����һ��
		flag = retry();
	} while (flag);
}

/*
* �Զ������̷߳���
*/
void GameController::moveDownInTime(long time) {
	while (background->gameStatus)
	{
		Sleep(time);
		// ����޷������ƶ� ������Ϸ�Ƿ����
		if (!safetyMoveDown())
		{
			safetyStatusCheck();
		};
	}
}

/*
* �̰߳�ȫ����Ϸ������������:���Ʒ���
* return �Ƿ�ɹ������ƶ�����
*/
bool GameController::safetyMoveDown() {
	m.lock();
	bool result = background->moveDown();
	// ������ɺ�չʾ����
	show();
	m.unlock();
	return result;
}

/*
* �̰߳�ȫ����Ϸ������������:���Ʒ���
* return �Ƿ�ɹ������ƶ�����
*/
bool GameController::safetyMoveLeft() {
	m.lock();
	bool result = background->moveLeft();
	// ������ɺ�չʾ����
	show();
	m.unlock();
	return result;
}

/*
* �̰߳�ȫ����Ϸ������������:���Ʒ���
* return �Ƿ�ɹ������ƶ�����
*/
bool GameController::safetyMoveRight() {
	m.lock();
	bool result = background->moveRight();
	// ������ɺ�չʾ����
	show();
	m.unlock();
	return result;
}

/*
* �̰߳�ȫ����Ϸ������������:�任��ǰ���鷽��
* return �Ƿ�ɹ��任��ǰ���鷽��
*/
bool GameController::safetyChangeDirection() {
	m.lock();
	bool result = background->changeDirection();
	// ������ɺ�չʾ����
	show();
	m.unlock();
	return result;
}

/*
* �̰߳�ȫ�ļ����Ϸ�Ƿ��������
*/
void GameController::safetyStatusCheck() {
	m.lock();
	background->shapeStop();
	score += (background->remove()) * 100;
	m.unlock();
}

/*
* ��ȡ�û����벢ִ�ж�Ӧ�����ķ���
*/
void GameController::userAction() {
	// ��Ϸѭ��
	while (background->getGameStatus())
	{
		// ��ȡ�û�����
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
* ��Ϸ�������� ��Ϸ����������÷�����Ϸ��������
* return ��Ϸ�Ƿ�ɹ�����
*/
void GameController::gameEnd() {
	system("cls");
	cout << "��Ϸ���������յ÷�:" << score << endl;
}

/*
* �Ƿ�����һ�η���
* return �Ƿ�����һ��
*/
bool GameController::retry() {
	char ch;
	// ���֮ǰ������
	cin.clear();
	cin.sync();
	cout << "����һ��������y,�������������ַ�" << endl;
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
	{
		return true;
	}
	return false;
}

/*
* չʾ��Ϸ��ǰ���淽��
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
* ���������Ϸ���淽��
*/
void GameController::print(int** pointer, int height, int weight, bool needDelete) {
	// ���������
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		// ÿ�п�ʼ
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
	// ����ײ���
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl << endl;
	// �����Ҫ�ͷ�
	if (needDelete)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] pointer[i];
		}
		delete[] pointer;
	}
}

// �����״��ǰ״̬
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