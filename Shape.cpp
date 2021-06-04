#include "Shape.h"


// �����ƶ����� ����ܹ������ƶ��򷵻�true
bool Shape::moveDown(Background& background) {
	// �������ϣ���������ѭ��ͼ�Σ��ж��ҵ��ĵ�һ��1�·��Ƿ���ʵ�� ֮��break
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = SHAPE_WEIGHT - 1; j >= 0; j--)
		{
			// ���ø��Ƿ�Ϊ1
			if (body[j][i])
			{
				// ��ⱳ���иø��·��Ƿ���ʵ��
				if (background.content[positionY + j + 1][positionX + i])
				{
					return false;
				}
				break;
			}
		}
	}
	// ȫ�������ɺ󣬻�û�б��赲 �������ƶ�һ��
	positionY += 1;
	return true;
}

// �����ƶ����� ����ܹ��ƶ����ƶ�������true
bool Shape::moveLeft(Background& background) {
	// �������� �������£�����Ƿ���ǽ�ڻ��߱���ס
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			// ���ÿ��Ƿ�Ϊ1
			if (body[i][j])
			{
				// ����������Ƿ�Ϊǽ�� ������ʵ��
				if ((positionX + j - 1 <= 0) ||
					(background.content[positionY + i][positionX + j - 1]))
				{
					return false;
				}
				break;
			}
		}
	}
	positionX -= 1;
	return true;
}

// ���Ʒ��� ����ܹ��ƶ�����true
bool Shape::moveRight(Background& background) {
	for (int i = SHAPE_HEIGHT - 1; i >= 0; i--)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++)
		{
			// ����Ƿ�ײǽ�����ұ���ʵ��
			if (body[j][i])
			{
				if ((positionX + i + 1 >= 20) ||
					(background.content[positionY + j][positionX + i + 1]))
				{
					return false;
				}
				break;
			}
		}
	}
	positionX += 1;
	return true;
}