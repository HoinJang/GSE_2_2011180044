#include "stdafx.h"
#include "Building.h"

Building::Building(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 100;
	Speed = 0.0f;
	LifeTime = 100000.0f;
	Life = 500.0;

	Color.r = 1.0f;
	Color.g = 1.0f;
	Color.b = 0.0f;
	Color.a = 1.0f;

	ParentNode = NULL;
	BulletTimer = 0.0f;
	b_texture = 0;
}

Building::~Building()
{
}

bool Building::CreateBullet(DWORD time)
{
	float sec = time / 1000.0f;
	BulletTimer += sec;
	if (BulletTimer > 1.0f)
	{
		BulletTimer = 0.0f;
		return true;
	}
	return false;
}

void Building::Render(Renderer * renderer)
{
	if (b_texture == 0)
	{
		if (Teamflag == Red)
		{
			b_texture = renderer->CreatePngTexture("./Resources/Building_Red.png");
		}
		else if(Teamflag == Blue)
		{
			b_texture = renderer->CreatePngTexture("./Resources/Building_Blue.png");
		}
	}
	renderer->DrawTexturedRect(Position.x,Position.y, 0.0, Size, Color.r, Color.g, Color.b, Color.a, b_texture);
}
void Building::Update(DWORD time)
{
	LifeTime -= 0.1f;
}

