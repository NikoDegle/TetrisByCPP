#include "Background.h"

Background::Background() {
	this->content[HEIGHT - 1][WEIGHT - 1] = { 0 };
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
			moveDown(i);
		}
	}
}

// 从某行开始 上面往下一行下落
void Background::moveDown(int& line) {
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
