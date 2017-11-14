#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Arrow : public Object
{
public:
	Arrow() {}
	Arrow(const float x, const float y, const int type);
	~Arrow();
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 
