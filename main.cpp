#include <iostream>
#include <Windows.h>
using namespace std;
#include "Background.h"
#include "ShapeLeftSeven.h"

void printShape(Shape& shape);	// �����״����
void print(int** pointer, int height, int weight, bool needDelete);	// ����κξ���ͼ�������
void fpsControl();	// ģ����Ļˢ�¿���


int main() {
	Background background;
	ShapeLeftSeven shapeLeftSeven;
	background.shapeNow = &shapeLeftSeven;

	print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	// �任״̬
	background.shapeNow->changeDirection(background);
	print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	// ��������
	for (int i = 0; i < 3; i++)
	{
		background.shapeNow->moveLeft(background);
		print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	}
	// ����2��
	for (int i = 0; i < 2; i++)
	{
		background.shapeNow->moveRight(background);
		print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	}
	// ����һ��
	for (int i = 0; i < 20; i++)
	{
		background.shapeNow->moveDown(background);
		print(background.backgroundNow(), HEIGHT, WEIGHT, true);
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

	// ÿ�������ģ����Ļ����
	fpsControl();
}

void fpsControl() {
	Sleep(1000);
	system("cls");
}