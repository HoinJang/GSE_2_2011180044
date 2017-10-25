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
	Direction.SetVector(1.0, 0.0, 0.0);
	Speed = 1.0;
	Life = 1000;
	LifeTime = 200000000;
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

void Object::Render(Renderer* renderer)
{
	renderer->DrawSolidRect(GetPositionX(),GetPositionY(),GetPositionZ(),GetSize(), GetColorRed(), GetColorGreen(), GetColorBlue(), 1);
}

void Object::Update(DWORD time)
{
	DWORD msToSecond = time * 0.01;
	this->Position.x = Position.x + Direction.x * Speed* time;
	this->Position.y = Position.y + Direction.y * Speed* time;
	this->Position.z = Position.z + Direction.z * Speed* time;

	this->Life -= 1;

	if (Position.x > 250)
		Direction.x = -Direction.x;
	if (Position.x < -250)
		Direction.x = -Direction.x;
	if (Position.y > 250)
		Direction.y = -Direction.y;
	if (Position.y < -250)
		Direction.y = -Direction.y;
}
