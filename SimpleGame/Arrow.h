#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>

class Arrow : public Object
{
private:
	bool erase_arrow;
public:
	Arrow() {}
	Arrow(const float x, const float y, const int type);
	~Arrow();
	bool GetErase() { return erase_arrow;}
public:
	void Render(Renderer* renderer);
	void Update(DWORD time);
}; 
