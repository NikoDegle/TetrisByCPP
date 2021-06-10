#include "GameController.h"
#include<iostream>
#include<mutex>
#include<thread>
#include<windows.h>	// Sleep����
#include<conio.h>	// �޻س���ȡ_getch()����
using namespace std;

#include "Background.h"

/*
* ��ʼ����Ϸ���������� ��Ҫ��ʼ����������ҷ���
*/
GameController::GameController() {
	background = nullptr;
	score = 0;
	moveDownTime = 1000;
	m = new mutex;
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
	if (m)
	{
		delete m;
		m = nullptr;
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
bool GameController::gameStart() {
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
	moveDownTimer.join();
	thread gameMainThread(&GameController::userAction, this);
	gameMainThread.join();
	// ��Ϸ������ֹͣ�߳�
	moveDownTimer.~thread();
	gameMainThread.~thread();
	gameEnd();
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
	m->lock();
	bool result = background->moveDown();
	m->unlock();
	return result;
}

/*
* �̰߳�ȫ����Ϸ������������:���Ʒ���
* return �Ƿ�ɹ������ƶ�����
*/
bool GameController::safetyMoveLeft() {
	m->lock();
	bool result = background->moveLeft();
	m->unlock();
	return result;
}

/*
* �̰߳�ȫ����Ϸ������������:���Ʒ���
* return �Ƿ�ɹ������ƶ�����
*/
bool GameController::safetyMoveRight() {
	m->lock();
	bool result = background->moveRight();
	m->unlock();
	return result;
}

/*
* �̰߳�ȫ����Ϸ������������:�任��ǰ���鷽��
* return �Ƿ�ɹ��任��ǰ���鷽��
*/
bool GameController::safetyChangeDirection() {
	m->lock();
	bool result = background->changeDirection();
	m->unlock();
	return result;
}

/*
* �̰߳�ȫ�ļ����Ϸ�Ƿ��������
*/
void GameController::safetyStatusCheck() {
	m->lock();
	background->shapeStop();
	score += (background->remove()) * 100;
	m->unlock();
}

/*
* ��ȡ�û����벢ִ�ж�Ӧ�����ķ���
*/
void GameController::userAction() {
	// ��Ϸѭ��
	while (background->getGameStatus())
	{
		// ��ȡ�û�����
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
	// ��Ϸ��������
	gameEnd();
}