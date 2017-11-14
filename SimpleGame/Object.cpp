#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::Object(const float x, const float y, const int type)
{
	this->Position.x = x;
	this->Position.y = y;
	Type = type;
}

Object::~Object()
{
}

void Object::setPosition(const float x, const float y)
{
	this->Position.x = x;
	this->Position.y = y;
}

void Object::setColor(const float r, const float g, const float b)
{
	this->Color.r = r;
	this->Color.g = g;
	this->Color.b = b;
}

void Object::setDirection(const float Vx, const float Vy)
{
	this->Direction.SetVector(Vx, Vy);
}

void Object::setSpeed(const float speed)
{
	this->Speed = speed;
}

void Object::Collision_Life(float num)
{
	Life -= num;
}
