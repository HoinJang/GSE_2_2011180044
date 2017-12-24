#pragma once
#include "Object.h"
#include "Renderer.h"
#include "MyDefine.h"

class Character_T2 : public Object
{
private:
	int spriteX;
	int spriteTime;
	bool Attack;
public:
	Character_T2() {}
	Character_T2(const float x, const float y, const int type, Team flag);
	~Character_T2();
public:
	void SetAttack(bool Attack)
	{
		this->Attack = Attack;
	}
	bool GetAttack()
	{
		return this->Attack;
	}
	void Update(DWORD time);
}; 