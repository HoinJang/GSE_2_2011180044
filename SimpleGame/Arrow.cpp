#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(const float x, const float y, const int type) : Object(x, y, type)
{
	Size = 2;
	Speed = 100.0f;
	LifeTime = 10000.0f;
	Life = 10.0f;

	Color.r = 0.0f;
	Color.g = 1.0f;
	Color.b = 0.0f;
	Color.a = 1.0f;

	Direction.x = (float)(rand() % 3 - 1);
	Direction.y = (float)(rand() % 3 - 1);
	if (Direction.x == 0)
		Direction.x = 1;
	if (Direction.y == 0)
		Direction.y = -1;

	ParentNode = NULL;
}

Arrow::~Arrow()
{
}

void Arrow::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, 0, Size, Color.r, Color.g, Color.b, Color.a);
}

void Arrow::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	Position.x += Direction.x * Speed * s;
	Position.y += Direction.y * Speed * s;

	if (Position.x <= -250 + Size / 2 || Position.x >= 250 - Size / 2)
		Direction.x = Direction.x * -1;
	if (Position.y <= -250 + Size / 2 || Position.y >= 250 - Size / 2)
		Direction.y = Direction.y * -1;
}
