#include "stdafx.h"
#include "Character_Type1.h"


Character_T1::Character_T1(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 40.0f;
	Speed = 200.0f;
	LifeTime = 10000.0f;
	Life = 100.0f;

	Direction.x = 1;
	Direction.y = 1;
	Direction.Nomalize();

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

Character_T1::~Character_T1()
{
	delete ParentNode;
	ParentNode = NULL;
}

void Character_T1::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	spriteTime += 1;

	Position.x += Direction.x * Speed * s;
	Position.y += Direction.y * Speed * s;

	if (Position.x <= -WindowWidth / 2 + Size / 2 || Position.x >= WindowWidth / 2 - Size / 2 )
		Direction.x = Direction.x * -1;
	if (Position.y <= -GameField / 2 + Size / 2  || Position.y >= GameField / 2 - Size / 2 )
		Direction.y = Direction.y * -1;

	LifeTime -= 0.1f;

	if (spriteTime > 200)
	{
		SpriteX += 1;
		spriteTime = 0;
	}
	if (SpriteX == 7)
	{
		SpriteX = 0;
	}
}
