#include "stdafx.h"
#include "Character_Type3.h"


Character_T3::Character_T3(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 50.0f;
	Speed = 20.0f;
	LifeTime = 1000.0f;
	Life = CHARACTERLIFE1;

	Direction.x = 0;
	Direction.y = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.Nomalize();

	if (Direction.y < 0)
		Direction.y = -Direction.y;
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
	ParentNode = NULL;

	spriteTime = 0;
	SpriteX = 0;

}

Character_T3::~Character_T3()
{
}

bool Character_T3::CreateArrow(DWORD time)
{
	float sec = time / 1000.0f;
	ArrowTimer += sec;

	if (ArrowTimer > ARROWTIMER)
	{
		ArrowTimer = 0.0f;
		return true;
	}
	return false;
}

void Character_T3::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	spriteTime += 1;

	Position.x += Direction.x * Speed * s;
	Position.y += Direction.y * Speed * s;

	if (Position.x <= -WindowWidth / 2 + Size / 2 || Position.x >= WindowWidth / 2 - Size / 2)
		Direction.x = Direction.x * -1;
	if (Position.y <= -GameField / 2 + Size / 2 || Position.y >= GameField / 2 - Size / 2)
		Direction.y = Direction.y * -1;

	LifeTime -= 0.1f;

	if (spriteTime > 350)
	{
		SpriteX += 1;
		spriteTime = 0;
	}
	if (SpriteX == 6)
	{
		SpriteX = 0;
	}
}
