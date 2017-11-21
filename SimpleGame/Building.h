#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Character.h"
#include <iostream>
class Building : public Object
{
private:
	float BulletTimer;
	GLuint b_texture;
public:
	Building() {}
	Building(const float x, const float y, const int type, Team flag);
 	~Building();
	bool CreateBullet(DWORD time);
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
};