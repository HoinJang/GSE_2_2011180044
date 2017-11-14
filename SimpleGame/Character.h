#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Character : public Object
{
private:
	float ArrowTimer;
public:
	Character() {}
	Character(const float x, const float y, const int type);
	~Character();
	bool CreateArrow(DWORD time);
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 