#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

/*
	����˹�������屳��
*/
#define HEIGHT 10
#define WEIGHT 20
class Background {
public:
	int content[HEIGHT][WEIGHT];

	Background();
	void remove();
	void moveDown(int& line);
};

#endif // !BACKGROUND_H

