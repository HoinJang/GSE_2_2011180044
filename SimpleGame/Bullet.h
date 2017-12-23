#pragma once

#include "Object.h"
#include "Renderer.h"
#include "MyDefine.h"

class Bullet : public Object
{
private:
	bool erase_bullet;
public:
	Bullet() {}
	Bullet(const float x, const float y, const int type, Team flag);
	~Bullet();
	bool GetErase() { return erase_bullet; }
public:
	void Update(DWORD time);
}; 