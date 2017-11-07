#include "stdafx.h"
#include "Character.h"

Character::Character(const float x, const float y, const float z, const int type) : Object(x, y, z, type)
{
	Size = 10;
	Speed = 300.0;
	LifeTime = 10000.0f;
	Life = 10.0;
	Direction.x = (float)(rand() % 3 - 1);
	Direction.y = (float)(rand() % 3 - 1);
	if (Direction.x == 0)
		Direction.x = 1;
	if (Direction.y == 0)
		Direction.y = -1;
	Direction.z = 0.0f;

	Color.r = 1.0f;
	Color.g = 1.0f;
	Color.b = 1.0f;
	Color.a = 1.0f;
}

Character::~Character()
{
}

void Character::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, Position.z, Size, Color.r, Color.g, Color.b, Color.a);
}

void Character::Update(DWORD time)
{
	float s = (float)time / 1000.0f;
	Position.x += Direction.x * Speed * s;
	Position.y += Direction.y * Speed * s;

	if (Position.x <= -250 + Size / 2 || Position.x >= 250 - Size / 2)
		Direction.x = Direction.x * -1;
	if (Position.y <= -250 + Size / 2 || Position.y >= 250 - Size / 2)
		Direction.y = Direction.y * -1;
}
