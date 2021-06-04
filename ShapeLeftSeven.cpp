#include "ShapeLeftSeven.h"

// ��ʼ��ͼ��7
ShapeLeftSeven::ShapeLeftSeven() {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			body[i][j] = 0;
		}
	}
	body[1][1] = body[1][2] = body[2][2] = body[3][2] = 1;
	this->positionX = 2;	// ���÷�����ֵ�ʱ���ڴ������ҵ����񣬶���
	this->positionY = 0;
}

// ������˳ʱ����ת90�� �����ݴ���temp�� ����Ƿ��赲
bool ShapeLeftSeven::changeDirection(Background& background) {
	int temp[SHAPE_HEIGHT][SHAPE_WEIGHT] = { 0 };
	// ˳ʱ����ת
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			temp[j][3 - i] = body[i][j];
		}
	}
	// ���������Ƿ�ǽ�������ұ��Ƿ�ǽ ����ת������ʵ���غ�
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			if (temp[i][j])
			{
				if (j + positionX <= 0 || j + positionX >= 20)
				{
					return false;
				}
				if (background.content[i + positionY][j + positionX])
				{
					return false;
				}
			}
		}
	}
	// ����״��ֵ
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			body[i][j] = temp[i][j];
		}
	}
	return true;
}