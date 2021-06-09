#pragma once

#ifndef BACKGROUND_H
#define BACKGROUND_H

/*
	����˹�������屳��
*/
#define HEIGHT 10
#define WEIGHT 20

// ����ȫ��������
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
	int content[HEIGHT][WEIGHT];	// ��Ϸ��
	Shape* shapeNow;	// ��ǰ���ڲ�����ͼ��
	Shape* shapeNext;	// ��һ��Ҫ������ͼ��
	bool gameStatus;	// ��ǰ��Ϸ״̬ ��ʼ��Ϊtrue ������Ϊfalse

	Background();
	Background& remove();	// ��鱳���е�ʵ���Ƿ���һ��Ϊ��
	void cleanLine(int& line);	// �������¸�������һ��
	Background& shapeStop();	// ��ǰͼ��ֹͣ��ת��Ϊ�����е�ʵ��
	int** backgroundNow();	// ���ص�ǰ�������˶��е�ͼ������
	Shape* createNextShape();	// ʹ�������������һ����״
	bool getGameStatus();	// ��ȡ��ǰ��Ϸ״̬

	// ��Ҳ�������
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool changeDirection();
};

#endif // !BACKGROUND_H

