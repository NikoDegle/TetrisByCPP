#include "Background.h"
#include "Shape.h"

Background::Background() {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WEIGHT; j++) {
			this->content[i][j] = 0;
		}
	}
}

// 检查是否有一行满的 如果有则将上面所有内容下移
void Background::remove() {
	// 循环方块并判断
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
}

// 从某行开始 上面往下一行下落
void Background::cleanLine(int& line) {
	// 如果是第0行 即最上面一行满了 将第0行置空
	if (line == 0)
	{
		for (int j = 0; j < WEIGHT; j++) {
			this->content[0][j] = 0;
		}
		return;
	}
	// 如果不是第0行 则往下落
	for (int i = line - 1; i > 0; i--)
	{
		for (int j = 0; j < WEIGHT; j++) {
			this->content[i + 1][j] = this->content[i][j];
		}
	}
}

// 当前图形停止并转换为背景中的实体
void Background::shapeStop() {
	// 先检测当前的形状是否存在
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
	// 获取下一个形状 TODO 创建一个新的形状放在next中
	delete shapeNow;
	shapeNow = shapeNext;
	shapeNext = nullptr;
}

// 返回当前形状与相对于背景的样子
int** Background::backgroundNow() {
	// 初始化一个当前的背景拷贝
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
	// 检测当前的形状是否存在
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

// 玩家操作方法
bool Background::moveDown() {
	// 判断当前指针是否存在
	if (shapeNow)
	{
		return shapeNow->moveDown(*this);
	}
	return false;
}

bool Background::moveRight() {
	// 判断当前指针是否存在
	if (shapeNow)
	{
		return shapeNow->moveRight(*this);
	}
	return false;
}

bool Background::moveLeft() {
	// 判断当前指针是否存在
	if (shapeNow)
	{
		return shapeNow->moveLeft(*this);
	}
	return false;
}

bool Background::changeDirection() {
	// 判断当前指针是否存在
	if (shapeNow)
	{
		return shapeNow->changeDirection(*this);
	}
	return false;
}