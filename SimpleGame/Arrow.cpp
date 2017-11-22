#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = ARROWBULLETSIZE;
	Speed = 100.0f;
	LifeTime = 10000.0f;
	Life = 10.0f;

	Direction.x = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.y = (((float)std::rand() / (float)RAND_MAX) - 0.5f);

	if (flag == Red)
	{
		Color.r = 0.5f;
		Color.g = 0.2f;
		Color.b = 0.7f;
		Color.a = 1.0f;
		if (Direction.y > 0)
		{
			Direction.y *= -1;
		}
	}
	else
	{
		Color.r = 1.0f;
		Color.g = 1.0f;
		Color.b = 0.0f;
		Color.a = 1.0f;
		if (Direction.y < 0)
		{
			Direction.y *= -1;
		}
	}
	// 교수님 코드 참고

	Direction.Nomalize();

	ParentNode = NULL;
	erase_arrow = false;
}

Arrow::~Arrow()
{
}

void Arrow::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, 0, Size, Color.r, Color.g, Color.b, Color.a, LEVEL_BULLETARROW);
}

void Arrow::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	Position.x += Direction.x * Speed * s ;
	Position.y += Direction.y * Speed * s ;

	if (Position.x <= -WindowWidth/2 + Size / 2 || Position.x >= WindowWidth/2 - Size / 2)
		erase_arrow = true;
	if (Position.y <= -WindowHeight + Size / 2 || Position.y >= WindowHeight/2 - Size / 2)
		erase_arrow = true;

	LifeTime -= 0.1f;
}
