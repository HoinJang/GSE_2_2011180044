#pragma once
#include <iostream>
#include <string>
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
	float PositionX, PositionY, PositionZ;
public:
	Object();
	~Object();

	int const GetType() { return Type; }
	float const GetSize() { return Size; }

	float const GetColorRed() { return Color.r; }
	float const GetColorGreen() { return Color.b; }
	float const GetColorBlue() { return Color.g; }

	float const GetPositionX() { return PositionX; }
	float const GetPositionY() { return PositionY; }
	float const GetPositionZ() { return PositionZ; }

	void setType(const int type) { this->Type = type; }
	void setSize(const float size) { this->Size = size; }
	void setPosition(const float x, const float y, const float z);
	void setColor(const float r, const float g, const float b);
public:
	void Update();
};