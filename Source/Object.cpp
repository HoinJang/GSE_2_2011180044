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
	this->PositionX = x;
	this->PositionY = y;
	this->PositionZ = z;
}

void Object::setColor(const float r, const float g, const float b)
{
	this->Color.r = r;
	this->Color.g = g;
	this->Color.b = b;
}
