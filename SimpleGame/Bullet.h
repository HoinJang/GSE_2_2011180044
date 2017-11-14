#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Bullet : public Object
{
private:
	bool erase_bullet;
public:
	Bullet() {}
	Bullet(const float x, const float y, const int type);
	~Bullet();
	bool GetErase() { return erase_bullet; }
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 