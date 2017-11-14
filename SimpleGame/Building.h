#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Character.h"
#include <iostream>
class Building : public Object
{
private:
	float BulletTimer;
public:
	Building() {}
	Building(const float x, const float y, const int type);
 	~Building();
	bool CreateBullet(DWORD time);
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
};