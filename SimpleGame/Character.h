#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Mydefine.h"
#include <iostream>

class Character : public Object
{
private:
	float ArrowTimer;
	GLuint c_texture;
	int spriteX;
	int spriteTime;
public:
	Character() {}
	Character(const float x, const float y, const int type, Team flag);
	~Character();
	bool CreateArrow(DWORD time);
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 