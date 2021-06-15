#pragma once

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

class Background;
class Shape;

/*
* ��Ϸ�������� ���ڿ�����Ϸ����
* @author: whc
*/
class GameController
{
public:
	// ��ʼ��
	GameController();
	// ����
	~GameController();
	// ��ȡ��Ϸ��������
	int getScore();
	// ��Ϸ��ʼ����
	void gameStart();
	// ��Ϸ��������
	void gameEnd();
	// �Ƿ�����һ��
	bool retry();

	static void print(int** pointer, int height, int weight, bool needDelete);	// �����������
	static void printShape(Shape& shape);	// ͼ���������

private:
	// ��Ҫ������Ϸ����
	Background* background;
	// �Ʒְ�
	int score;
	// �����Զ������ٶ�
	long moveDownTime;


	// �Զ������ʱ����
	void moveDownInTime(long time);
	// �û�����������
	void userAction();
	// ��ȡ��Ϸ�������� �÷�����Ҫʹ��mutex����ȷ�����̰߳�ȫ
	Background* getBackground();
	// չʾ��Ϸ���淽��
	void show();
	// �̰߳�ȫ����Ϸ��������
	bool safetyMoveDown();
	bool safetyMoveRight();
	bool safetyMoveLeft();
	bool safetyChangeDirection();
	void safetyStatusCheck();	// �����Ϸ�Ƿ��������
};

#endif // !GAME_CONTROLLER_H



