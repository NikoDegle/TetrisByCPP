#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
#include "Background.h"
#include "ShapeLeftSeven.h"
#include "ShapeRightSeven.h"
#include "ShapeSquare.h"
#include "ShapeBugget.h"
#include "ShapeTrangle.h"
#include "ShapeRightZed.h"
#include "ShapeLeftZed.h"

void printShape(Shape& shape);	// �����״����
void print(int** pointer, int height, int weight, bool needDelete);	// ����κξ���ͼ�������
void fpsControl();	// ģ����Ļˢ�¿���
void printControl(Background& background);	// �����ʽ���ƹ���

int main() {
	Background background;
	vector<Shape*> vector;
	vector.push_back(new ShapeLeftSeven);
	vector.push_back(new ShapeRightSeven);
	vector.push_back(new ShapeSquare);
	vector.push_back(new ShapeBugget);
	vector.push_back(new ShapeTrangle);
	vector.push_back(new ShapeRightZed);
	vector.push_back(new ShapeLeftZed);
	background.shapeNow = vector.back();
	vector.pop_back();
	background.shapeNext = vector.back();
	vector.pop_back();

	printControl(background);

	// ����ǰ��״���е�ʱ��
	while (background.shapeNow)
	{
		// ��ǰ��״�����ĸ�
		for (int i = 0; i < 4; i++)
		{
			if (background.moveDown()) {
				printControl(background);
			}
		}
		// �任��̬�Ĵ�
		for (int i = 0; i < 4; i++)
		{
			if (background.changeDirection())
			{
				printControl(background);
			}
		}
		// ��ǰvectorʣ��˫���������ĸ� ���������ĸ�
		if (vector.size() % 2)
		{
			for (int i = 0; i < 4; i++)
			{
				if (background.moveRight())
				{
					printControl(background);
				}
			}
		}
		else {
			for (int i = 0; i < 4; i++)
			{
				if (background.moveLeft())
				{
					printControl(background);
				}
			}
		}
		// ͼ���䵽�ײ�
		while (background.shapeNow)
		{
			if (background.moveDown())
			{
				printControl(background);
				continue;
			}
			background.shapeStop();
			if (!vector.empty())
			{
				background.shapeNext = vector.back();
				vector.pop_back();
			}
			break;
		}
	}
	return 0;
}

// �����״��ǰ״̬
void printShape(Shape& shape) {
	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WEIGHT; j++) {
			if (shape.body[i][j])
			{
				cout << "*";
			}
			else {
				cout << "+";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}

void print(int** pointer, int height, int weight, bool needDelete) {
	// ���������
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		// ÿ�п�ʼ
		cout << "|";
		for (int j = 0; j < weight; j++) {
			if (pointer[i][j])
			{
				cout << "*";
			}
			else {
				cout << " ";
			}
		}
		cout << "|" << endl;
	}
	// ����ײ���
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl << endl;
	// �����Ҫ�ͷ�
	if (needDelete)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] pointer[i];
		}
		delete[] pointer;
	}
}

void fpsControl() {
	Sleep(500);
	system("cls");
}

void printControl(Background& background) {
	print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	cout << "next:" << endl;
	if (background.shapeNext)
	{
		printShape(*background.shapeNext);
	}
	fpsControl();
}