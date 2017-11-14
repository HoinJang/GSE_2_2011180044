#include "stdafx.h"
#include "Building.h"

Building::Building(const float x, const float y, const int type) : Object(x, y, type)
{
	Size = 50;
	Speed = 0.0f;
	LifeTime = 10000.0f;
	Life = 500.0;

	Color.r = 1.0f;
	Color.g = 1.0f;
	Color.b = 0.0f;
	Color.a = 1.0f;

	ParentNode = NULL;
	BulletTimer = 0.0f;
}

Building::~Building()
{
}

bool Building::CreateBullet(DWORD time)
{
	float sec = time / 1000.0f;
	BulletTimer += sec;
	if (BulletTimer > 0.5f)
	{
		BulletTimer = 0.0f;
		return true;
	}
	return false;
}

void Building::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, 0.0f, Size, Color.r, Color.g, Color.b, Color.a);
}
void Building::Update(DWORD time)
{
	LifeTime -= 0.1f;
}

