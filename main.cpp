#include <iostream>
#include <Windows.h>
using namespace std;
#include "Background.h"
#include "ShapeLeftSeven.h"

void printShape(Shape& shape);	// 输出形状样子
void print(int** pointer, int height, int weight, bool needDelete);	// 输出任何矩形图像的样子
void fpsControl();	// 模拟屏幕刷新控制


int main() {
	Background background;
	ShapeLeftSeven shapeLeftSeven;
	background.shapeNow = &shapeLeftSeven;

	print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	// 变换状态
	background.shapeNow->changeDirection(background);
	print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	// 左移三格
	for (int i = 0; i < 3; i++)
	{
		background.shapeNow->moveLeft(background);
		print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	}
	// 右移2格
	for (int i = 0; i < 2; i++)
	{
		background.shapeNow->moveRight(background);
		print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	}
	// 下移一格
	for (int i = 0; i < 20; i++)
	{
		background.shapeNow->moveDown(background);
		print(background.backgroundNow(), HEIGHT, WEIGHT, true);
	}
	return 0;
}

// 输出形状当前状态
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
	// 输出顶部框
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		// 每行开始
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
	// 输出底部框
	for (int i = 0; i < weight; i++)
	{
		cout << "-";
	}
	cout << endl << endl;
	// 如果需要释放
	if (needDelete)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] pointer[i];
		}
		delete[] pointer;
	}

	// 每次输出后模拟屏幕控制
	fpsControl();
}

void fpsControl() {
	Sleep(1000);
	system("cls");
}