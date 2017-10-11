#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	Type = BACKGROUND;
	Size = 10.0;
	Color.r = 1.0;
	Color.g = 1.0;
	Color.b = 1.0;
	PositionX = 0.0;
	PositionY = 0.0;
	PositionZ = 0.0;
}

Object::~Object()
{
}

void Object::setPosition(const float x, const float y, const float z)
{
	PositionX = x;
	PositionY = y;
	PositionZ = z;
}

void Object::setColor(const float r, const float g, const float b)
{
	Color.r = r;
	Color.g = g;
	Color.b = b;
}