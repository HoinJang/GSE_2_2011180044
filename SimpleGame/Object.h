#pragma once
#include <iostream>
#include <string>
#include "MyVector.h"
#include "Renderer.h"

using namespace std;

enum Type
{
	BACKGROUND = 0,
	BUILDING,
	TRAP,
	CHARACTER,
	UNIT,
	BULLET
};
typedef struct ObjectC
{
	float r;
	float g;
	float b;
}ObjectC;

class Object
{
private:
	int Type;
	float Size;
	float Speed;
	ObjectC Color;
	MyVector Position;
	MyVector Direction;
	int Life;
	int LifeTime;
public:
	Object();
	~Object();

	int const GetType() { return Type; }
	float const GetSize() { return Size; }

	float const GetColorRed() { return Color.r; }
	float const GetColorGreen() { return Color.g; }
	float const GetColorBlue() { return Color.b; }

	float const GetPositionX() { return Position.x; }
	float const GetPositionY() { return Position.y; }
	float const GetPositionZ() { return Position.z; }
	int const GetLife() { return Life; }

	void setType(const int type) { this->Type = type; }
	void setSize(const float size) { this->Size = size; }
	void setPosition(const float x, const float y, const float z);
	void setColor(const float r, const float g, const float b);
	void setDirection(const float Vx, const float Vy, const float Vz);
	void setSpeed(const float speed);
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
};