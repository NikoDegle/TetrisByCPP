#include "Shape.h"
#include "Background.h"


// �����ƶ����� ����ܹ������ƶ��򷵻�true
bool Shape::moveDown(Background& background) {
	// �������ϣ���������ѭ��ͼ�Σ��ж��ҵ��ĵ�һ��1�·��Ƿ���ʵ�� ֮��break
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = SHAPE_WEIGHT - 1; j >= 0; j--)
		{
			// ���ø��Ƿ�Ϊ1 ���Ҹø��·��Ƿ��ڱ�����
			if (body[j][i] && (positionY + j + 1 >= 0))
			{
				// ���ø��Ƿ���ǽ ���� �����иø��·��Ƿ���ʵ��
				if ((positionY + j + 1 > 9) || background.content[positionY + j + 1][positionX + i])
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
			// ���ÿ��Ƿ�Ϊ1 ���Ҹÿ��Ѿ����뱳��
			if (body[i][j] && (positionY + i >= 0))
			{
				// ����������Ƿ�Ϊǽ�� ������ʵ��
				if ((positionX + j - 1 < 0) ||
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
			// ����Ƿ�ײǽ�����ұ���ʵ�� �����Ѿ����뱳����
			if (body[j][i] && (positionY + j >= 0))
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

// ������˳ʱ����ת90�� �����ݴ���temp�� ����Ƿ��赲
bool Shape::changeDirection(Background& background) {
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
				if (background.content[i + positionY][j + positionX] && (i + positionY >= 0))
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