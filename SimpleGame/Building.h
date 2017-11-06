#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Building : public Object
{
public:
	Building() {}
	Building(const float x, const float y, const float z, const int type);
 	~Building();
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
};