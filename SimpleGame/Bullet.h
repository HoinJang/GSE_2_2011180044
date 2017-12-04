#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include "Mydefine.h"

class Bullet : public Object
{
private:
	bool erase_bullet;
	GLuint m_texture;
	float m_paticletime;
public:
	Bullet() {}
	Bullet(const float x, const float y, const int type, Team flag);
	~Bullet();
	bool GetErase() { return erase_bullet; }
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 