#include "ShapeLeftSeven.h"
#include "Background.h"

// ��ʼ��ͼ��7
ShapeLeftSeven::ShapeLeftSeven() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][1] = body[1][2] = body[2][2] = body[3][2] = 1;
	this->positionX = 4;	// ���÷�����ֵ�ʱ���ڴ������ҵ����񣬶���
	this->positionY = -1;
}