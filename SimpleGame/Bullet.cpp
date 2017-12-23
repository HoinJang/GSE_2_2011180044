#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = ARROWBULLETSIZE ;
	Speed = 250.0f;
	LifeTime = 10000.0f;
	Life = ARROWBULLETLIFE;

	Direction.x = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.y = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	// 교수님 코드 참고

	if (flag == Red)
	{
		Color.r = 1.0f;
		Color.g = 0.0f;
		Color.b = 0.0f;
		Color.a = 1.0f;
		if (Direction.y > 0)
		{
			Direction.y *= -1;
		}
	}
	else
	{
		Color.r = 0.0f;
		Color.g = 0.0f;
		Color.b = 1.0f;
		Color.a = 1.0f;
		if (Direction.y < 0)
		{
			Direction.y *= -1;
		}
	}
	Direction.Nomalize();
	ParentNode = NULL;
	erase_bullet = false;

	m_paticletime = 0.0;
}
Bullet::~Bullet()
{

}
void Bullet::Update(DWORD time)
{
	float s = (float)time / 1000.0f;
	m_paticletime += s;

	Position.x += Direction.x * Speed * s ;
	Position.y += Direction.y * Speed * s ;

	if (Position.x <= -WindowWidth / 2 + Size / 2 || Position.x >= WindowWidth / 2 - Size / 2)
		erase_bullet = true;
	if (Position.y <= -GameField/2 + Size / 2 || Position.y >= GameField /2 - Size / 2)
		erase_bullet = true;

	LifeTime -= 0.1f;
}
