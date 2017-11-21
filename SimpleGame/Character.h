#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Mydefine.h"
#include <iostream>

class Character : public Object
{
private:
	float ArrowTimer;
public:
	Character() {}
	Character(const float x, const float y, const int type, Team flag);
	~Character();
	bool CreateArrow(DWORD time);
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 