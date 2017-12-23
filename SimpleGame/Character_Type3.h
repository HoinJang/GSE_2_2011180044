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
public:
	Character_T3() {}
	Character_T3(const float x, const float y, const int type, Team flag);
	~Character_T3();
	bool CreateArrow(DWORD time);
public:
	void Update(DWORD time);
};