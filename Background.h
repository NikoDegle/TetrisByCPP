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

class Background {
public:
	int content[HEIGHT][WEIGHT];	// ��Ϸ��
	Shape* shapeNow;	// ��ǰ���ڲ�����ͼ��
	Shape* shapeNext;	// ��һ��Ҫ������ͼ��

	Background();
	void remove();
	void cleanLine(int& line);
	void shapeStop();	// ��ǰͼ��ֹͣ��ת��Ϊ�����е�ʵ��
	int** backgroundNow();	// ���ص�ǰ�������˶��е�ͼ������

	// ��Ҳ�������
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool changeDirection();
};

#endif // !BACKGROUND_H

