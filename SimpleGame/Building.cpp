#include "stdafx.h"
#include "Building.h"

Building::Building(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 100.0f;
	Speed = 0.0f;
	LifeTime = 100000.0f;
	Life = BUILDINGLIFE;
	ParentNode = NULL;
	BulletTimer = 0.0f;

	if (flag == Red)
	{
		Color.r = 1.0f;
		Color.g = 0.0f;
		Color.b = 0.0f;
		Color.a = 0.0f;
	}
	else if (flag == Blue)
	{
		Color.r = 0.0f;
		Color.g = 0.0f;
		Color.b = 1.0f;
		Color.a = 0.0f;
	}
}
Building::~Building()
{
}
bool Building::CreateBullet(DWORD time)
{
	float sec = time / 1000.0f;
	BulletTimer += sec;
	if (BulletTimer > BULLETTIMER)
	{
		BulletTimer = 0.0f;
		return true;
	}
	return false;
}
void Building::Update(DWORD time)
{
}

