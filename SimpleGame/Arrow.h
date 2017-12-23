#pragma once
#include "Object.h"
#include "Renderer.h"
#include "MyDefine.h"

class Arrow : public Object
{
private:
	bool erase_arrow;
public:
	Arrow() {}
	Arrow(const float x, const float y, const int type, Team flag);
	~Arrow();
	bool GetErase() { return erase_arrow;}
public:
	void Update(DWORD time);
}; 
