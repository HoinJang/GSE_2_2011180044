#pragma once
#include <iostream>
#include <string>
#include "MyVector.h"

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
	ObjectC Color;
	MyVector Position;
	MyVector Speed;
public:
	Object();
	~Object();

	int const GetType() { return Type; }
	float const GetSize() { return Size; }

	float const GetColorRed() { return Color.r; }
	float const GetColorGreen() { return Color.b; }
	float const GetColorBlue() { return Color.g; }

	float const GetPositionX() { return Position.x; }
	float const GetPositionY() { return Position.y; }
	float const GetPositionZ() { return Position.z; }

	void setType(const int type) { this->Type = type; }
	void setSize(const float size) { this->Size = size; }
	void setPosition(const float x, const float y, const float z);
	void setColor(const float r, const float g, const float b);
public:
	void Update();
};