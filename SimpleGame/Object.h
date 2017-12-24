#pragma once
#include "stdafx.h"
#include "MyVector.h"
#include "MyDefine.h"
#include "Renderer.h"

using namespace std;

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
	float Life;
	float LifeTime;
	ObjectC Color;
	MyVector Position;
	MyVector Direction;
	Object* ParentNode;
	Team Teamflag;
	int SpriteX;
	int SpriteY;
	float m_paticletime;
public:
	Object();
	Object(const float x, const float y, const int type, Team flag);
	virtual ~Object();
public:
	int const GetType() { return Type; }
	float const GetSize() { return Size; }
	float const GetColorRed() { return Color.r; }
	float const GetColorGreen() { return Color.g; }
	float const GetColorBlue() { return Color.b; }
	float const GetColorAlpha() { return Color.a; }
	float const GetPositionX() { return Position.x; }
	float const GetPositionY() { return Position.y; }
	float const GetLife() { return Life; }
	float const GetLifeTime() { return LifeTime; }
	int const GetSpriteX() { return SpriteX; }
	int const GetSpriteY() { return SpriteY; }
	float GetDirectionX() { return Direction.x; }
	float GetDirectionY() { return Direction.y; }
	float const GetParticleTime() { return m_paticletime; }
	Team const GetTeamFlag() { return Teamflag; }
	Object* const GetParentNode() { return ParentNode; }

	void setType(const int type) { this->Type = type; }
	void setSize(const float size) { this->Size = size; }
	void setParentNode(Object* Node) { this->ParentNode = Node; }
	void setPosition(const float x, const float y);
	void setColor(const float r, const float g, const float b, const float a);
	void setDirection(const float Vx, const float Vy);
	void setSpeed(const float speed);
	void Collision_Life(float num);
public:
	virtual void Update(DWORD time) =0 ;
};