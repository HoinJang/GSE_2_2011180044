#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 2;
	Speed = 600.0f;
	LifeTime = 10000.0f;
	Life = 20.0f;


	Direction.x = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.y = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	// 교수님 코드 참고
	if (flag == Red)
	{
		Color.r = 1.0f;
		Color.g = 0.0f;
		Color.b = 0.0f;
		Color.a = 1.0f;
	}
	else
	{
		Color.r = 0.0f;
		Color.g = 0.0f;
		Color.b = 1.0f;
		Color.a = 1.0f;
	}

	ParentNode = NULL;
	erase_bullet = false;
}

Bullet::~Bullet()
{
}

void Bullet::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, 0.0f, Size, Color.r, Color.g, Color.b, Color.a);
}

void Bullet::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	Position.x += Direction.x * Speed * s * 3;;
	Position.y += Direction.y * Speed * s * 3;;

	if (Position.x <= -WindowWidth / 2 + Size / 2 || Position.x >= WindowWidth / 2 - Size / 2)
		erase_bullet = true;
	if (Position.y <= -WindowHeight/2 + Size / 2 || Position.y >= WindowHeight/2 - Size / 2)
		erase_bullet = true;

	LifeTime -= 0.1f;
}
