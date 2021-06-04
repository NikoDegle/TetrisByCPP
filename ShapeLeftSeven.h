#pragma once
#include "Shape.h"
#include "Background.h"
#ifndef SHAPE_LEFT_SEVEN_H
#define SHAPE_LEFT_SEVEN_H

class ShapeLeftSeven : public Shape
{
public:
	ShapeLeftSeven();
	bool changeDirection(Background& background);
};


#endif // !SHAPE_SEVEN_H


