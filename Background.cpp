#include "Background.h"

Background::Background() {
	this->content[HEIGHT - 1][WEIGHT - 1] = { 0 };
}

// ����Ƿ���һ������ �����������������������
void Background::remove() {
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
			moveDown(i);
		}
	}
}

// ��ĳ�п�ʼ ��������һ������
void Background::moveDown(int& line) {
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
