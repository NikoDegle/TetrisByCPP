#include "ShapeTrangle.h"

ShapeTrangle::ShapeTrangle() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[2][0] = body[2][1] = body[2][2] = body[1][1] = 1;
	// ���÷�����ֵ�ʱ���λ��
	this->positionX = START_X;
	this->positionY = START_Y;
}