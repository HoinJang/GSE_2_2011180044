#pragma once
#include "Object.h"
#include "Renderer.h"
#include "MyDefine.h"

class Character_T3 : public Object
{
private:
	float ArrowTimer;
	GLuint c_texture;
	int spriteX;
	int spriteTime;
	bool Move;
	int EnemyIndex;
public:
	Character_T3() {}
	Character_T3(const float x, const float y, const int type, Team flag);
	~Character_T3();
public:
	bool CreateArrow(DWORD time);
	bool GetMove()
	{
		return this->Move;
	}
	void SetMove(bool Move)
	{
		this->Move = Move;
	}
	int GetIndex()
	{
		return this->EnemyIndex;
	}
	void SetIndex(int index)
	{
		this->EnemyIndex = index;
	}
public:
	void Update(DWORD time);
};