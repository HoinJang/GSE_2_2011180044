#include "stdafx.h"
#include "Building.h"

Building::Building(const float x, const float y, const float z, const int type) : Object(x, y, z, type)
{
	Size = 50;
	Speed = 0.0f;
	LifeTime = 10000.0f;
	Life = 500.0f;

	Color.r = 1.0f;
	Color.g = 1.0f;
	Color.b = 0.0f;
	Color.a = 1.0f;
}

Building::~Building()
{
}

void Building::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, Position.z, Size, Color.r, Color.g, Color.b, Color.a);
}

void Building::Update(DWORD time)
{
	LifeTime -= 1.0f;
}
