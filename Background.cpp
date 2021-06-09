#include <stdlib.h>
#include <time.h>

#include "Background.h"
#include "Shape.h"
#include "ShapeBugget.h"
#include "ShapeLeftSeven.h"
#include "ShapeLeftZed.h"
#include "ShapeRightSeven.h"
#include "ShapeRightZed.h"
#include "ShapeSquare.h"
#include "ShapeTrangle.h"

Background::Background() {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WEIGHT; j++) {
			this->content[i][j] = 0;
		}
	}
	shapeNext = createNextShape();
	shapeNow = createNextShape();
}

// ����Ƿ���һ������ �����������������������
Background& Background::remove() {
	// ѭ�����鲢�ж�
	for (int i = 0; i < HEIGHT; i++)
	{
		int count = 0;
		for (int j = 0; j < WEIGHT; j++)
		{
			count += this->content[i][j];
		}
		if (count == 20)
		{
			cleanLine(i);
		}
	}
	return *this;
}

// ��ĳ�п�ʼ ��������һ������
void Background::cleanLine(int& line) {
	// ����ǵ�0�� ��������һ������ ����0���ÿ�
	if (line == 0)
	{
		for (int j = 0; j < WEIGHT; j++) {
			this->content[0][j] = 0;
		}
		return;
	}
	// ������ǵ�0�� ��������
	for (int i = line - 1; i > 0; i--)
	{
		for (int j = 0; j < WEIGHT; j++) {
			this->content[i + 1][j] = this->content[i][j];
		}
	}
}

// ��ǰͼ��ֹͣ��ת��Ϊ�����е�ʵ��
Background& Background::shapeStop() {
	// �ȼ�⵱ǰ����״�Ƿ����
	if (shapeNow)
	{
		for (int i = 0; i < SHAPE_HEIGHT; i++)
		{
			for (int j = 0; j < SHAPE_WEIGHT; j++)
			{
				if (shapeNow->body[i][j])
				{
					content[shapeNow->positionY + i][shapeNow->positionX + j] += shapeNow->body[i][j];
				}
			}
		}
	}
	// ��ȡ��һ����״
	delete shapeNow;
	shapeNow = shapeNext;
	shapeNext = createNextShape();
	return *this;
}

// ���ص�ǰ��״������ڱ���������
int** Background::backgroundNow() {
	// ��ʼ��һ����ǰ�ı�������
	int** temp = new int*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++)
	{
		temp[i] = new int[WEIGHT];
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WEIGHT; j++)
		{
			temp[i][j] = content[i][j];
		}
	}
	// ��⵱ǰ����״�Ƿ����
	if (shapeNow)
	{
		for (int i = 0; i < SHAPE_HEIGHT; i++)
		{
			for (int j = 0; j < SHAPE_WEIGHT; j++)
			{
				if (shapeNow->body[i][j] && (shapeNow->positionY + i >= 0))
				{
					temp[shapeNow->positionY + i][shapeNow->positionX + j] += shapeNow->body[i][j];
				}
			}
		}
	}

	return temp;
}

// ��Ҳ�������
bool Background::moveDown() {
	// �жϵ�ǰָ���Ƿ����
	if (shapeNow)
	{
		return shapeNow->moveDown(*this);
	}
	return false;
}

bool Background::moveRight() {
	// �жϵ�ǰָ���Ƿ����
	if (shapeNow)
	{
		return shapeNow->moveRight(*this);
	}
	return false;
}

bool Background::moveLeft() {
	// �жϵ�ǰָ���Ƿ����
	if (shapeNow)
	{
		return shapeNow->moveLeft(*this);
	}
	return false;
}

bool Background::changeDirection() {
	// �жϵ�ǰָ���Ƿ����
	if (shapeNow)
	{
		return shapeNow->changeDirection(*this);
	}
	return false;
}

/*
	�������ɵ������ȡ��7 �õ����������ɶ�Ӧ����״
	reutrn ���ɵ���״ָ��
*/
Shape* Background::createNextShape() {
	srand((unsigned int)(time(NULL)));
	int ShapeType = rand() % 7;
	switch (ShapeType)
	{
	case 0:	return new ShapeBugget;
	case 1: return new ShapeLeftSeven;
	case 2: return new ShapeLeftZed;
	case 3: return new ShapeRightSeven;
	case 4: return new ShapeRightZed;
	case 5: return new ShapeSquare;
	case 6: return new ShapeTrangle;
	default:
		return new ShapeSquare;
	}
}