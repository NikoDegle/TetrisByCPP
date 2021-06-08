#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
#include "Background.h"
#include "ShapeLeftSeven.h"
#include "ShapeRightSeven.h"
#include "ShapeSquare.h"

void printShape(Shape& shape);	// 输出形状样子
void print(int** pointer, int height, int weight, bool needDelete);	// 输出任何矩形图像的样子
void fpsControl();	// 模拟屏幕刷新控制
void printControl(Background& background);	// 输出格式控制工具

int main() {
	Background background;
	vector<Shape*> vector;
	vector.push_back(new ShapeLeftSeven);
	vector.push_back(new ShapeRightSeven);
	vector.push_back(new ShapeSquare);
	vector.push_back(new ShapeLeftSeven);
	vector.push_back(new ShapeLeftSeven);
	background.shapeNow = vector.back();
	vector.pop_back();
	background.shapeNext = vector.back();
	vector.pop_back();

	printControl(background);
	// 变换状态
	if (background.changeDirection())
	{
		printControl(background);
	}
	// 左移三格
	for (int i = 0; i < 3; i++)
	{
		if (background.moveLeft())
		{
			printControl(background);
		}
	}
	// 右移2格
	for (int i = 0; i < 2; i++)
	{
		if (background.moveRight())
		{
			printControl(background);
		}
	}
	// 下移一格
	while (background.shapeNow)
	{
		if (!background.moveDown())
		{
			background.shapeStop();
			if (!vector.empty())
			{
				background.shapeNext = vector.back();
				vector.pop_back();
			}	
		}
		printControl(background);
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