#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::Object(const float x, const float y, const float z, const int type)
{
	this->Position.x = x;
	this->Position.y = y;
	this->Position.z = z;
	Type = type;
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

void Object::setDirection(const float Vx, const float Vy, const float Vz)
{
	this->Direction.SetVector(Vx, Vy, Vz);
}

void Object::setSpeed(const float speed)
{
	this->Speed = speed;
}
