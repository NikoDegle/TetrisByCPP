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
	printControl(background);

	// ��Ϸ����������
	while(background.getGameStatus())
	{
		// ��ǰ��״�����ĸ�
		for (int i = 0; i < 3; i++)
		{
			if (background.moveDown()) {
				printControl(background);
			}
		}
		// �任��̬�Ĵ�
		for (int i = 0; i < 3; i++)
		{
			if (background.changeDirection())
			{
				printControl(background);
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
			background.shapeStop().remove();
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
	Sleep(100);
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