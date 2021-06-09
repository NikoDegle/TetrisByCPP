#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#define SHAPE_HEIGHT 4
#define SHAPE_WEIGHT 4
#define START_X 7
#define START_Y -2

// ����ȫ��������
class Background;

class Shape
{
public:
	int body[SHAPE_HEIGHT][SHAPE_WEIGHT];
	int positionX;	// x��λ��
	int positionY;	// y��λ��
	bool changeDirection(Background& background); // �޸ķ���
	bool moveLeft(Background& background); // ����
	bool moveRight(Background& background);	// ����
	bool moveDown(Background& background);	// ����
};

#endif // !SHAPE_H


