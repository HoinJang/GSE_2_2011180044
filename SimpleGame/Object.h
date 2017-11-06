#pragma once
#include <iostream>
#include <string>
#include "stdafx.h"
#include "MyVector.h"
#include "Renderer.h"

using namespace std;

enum Type
{
	BUILDING = 0,
	CHARACTER,
	BULLET,
	ARROW
};
typedef struct ObjectC
{
	float r;
	float g;
	float b;
	float a;
}ObjectC;

class Object
{
protected:
	int Type;
	float Size;
	float Speed;
	ObjectC Color;
	MyVector Position;
	MyVector Direction;
	float Life;
	float LifeTime;
public:
	Object();
	Object(const float x, const float y, const float z, const int type);
	virtual ~Object();
	int const GetType() { return Type; }
	float const GetSize() { return Size; }
	float const GetColorRed() { return Color.r; }
	float const GetColorGreen() { return Color.g; }
	float const GetColorBlue() { return Color.b; }
	float const GetPositionX() { return Position.x; }
	float const GetPositionY() { return Position.y; }
	float const GetPositionZ() { return Position.z; }
	float const GetLife() { return Life; }
	float const GetLifeTime() { return LifeTime; }
	void setType(const int type) { this->Type = type; }
	void setSize(const float size) { this->Size = size; }
	void setPosition(const float x, const float y, const float z);
	void setColor(const float r, const float g, const float b);
	void setDirection(const float Vx, const float Vy, const float Vz);
	void setSpeed(const float speed);
	//
public:
	virtual void Render(Renderer* renderer) =0;
	virtual void Update(DWORD time) =0 ;
};