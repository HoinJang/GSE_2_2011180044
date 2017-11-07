#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Bullet : public Object
{
public:
	Bullet() {}
	Bullet(const float x, const float y, const float z, const int type);
	~Bullet();
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 