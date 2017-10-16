#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	Type = BACKGROUND;
	Size = 10.0;
	Color.r = 1.0;
	Color.g = 1.0;
	Color.b = 1.0;
	Position.x = 0.0;
	Position.y = 0.0;
	Position.z = 0.0;
	Speed.SetVector(1.0, 0.0, 0.0);
}

Object::~Object()
{
}

void Object::setPosition(const float x, const float y, const float z)
{
	this->Position.x = x;
	this->Position.y = y;
	this->Position.z = z;
}

void Object::setColor(const float r, const float g, const float b)
{
	this->Color.r = r;
	this->Color.g = g;
	this->Color.b = b;
}

void Object::Update()
{
	this->Position.x = Position.x + Speed.x;
	this->Position.y = Position.y + Speed.y;
	this->Position.z = Position.z + Speed.z;
}
