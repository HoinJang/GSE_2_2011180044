#pragma once
#include "Object.h"
#include "Renderer.h"
#include "MyDefine.h"

class Character_T1 : public Object
{
private:
	float ArrowTimer;
	GLuint c_texture;
	int spriteX;
	int spriteTime;
public:
	Character_T1() {}
	Character_T1(const float x, const float y, const int type, Team flag);
	~Character_T1();
public:
	void Update(DWORD time);
};