#include "ShapeSquare.h"

ShapeSquare::ShapeSquare() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][1] = body[1][2] = body[2][2] = body[2][1] = 1;
	this->positionX = START_X;	// ���÷�����ֵ�ʱ���ڴ������ҵ����񣬶���
	this->positionY = START_Y;
}