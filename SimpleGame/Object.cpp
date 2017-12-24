#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::Object(const float x, const float y, const int type, Team flag)
{
	this->Position.x = x;
	this->Position.y = y;
	Type = type;
	Teamflag = flag;
}

Object::~Object()
{
}

void Object::setPosition(const float x, const float y)
{
	this->Position.x = x;
	this->Position.y = y;
}

void Object::setColor(const float r, const float g, const float b, const float a)
{
	this->Color.r = r;
	this->Color.g = g;
	this->Color.b = b;
	this->Color.a = a;
}

void Object::setDirection(const float Vx, const float Vy)
{
	this->Direction.SetVector(Vx, Vy);
	this->Direction.Nomalize();
}

void Object::setSpeed(const float speed)
{
	this->Speed = speed;
}

void Object::Collision_Life(float num)
{
	Life -= num;
}
