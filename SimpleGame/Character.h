#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Character : public Object
{
public:
	Character() {}
	Character(const float x, const float y, const float z, const int type);
	~Character();
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 