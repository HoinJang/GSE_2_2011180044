#include "stdafx.h"
#include "Character.h"

Character::Character(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 10;
	Speed = 300.0f;
	LifeTime = 10000.0f;
	Life = 10.0;


	Direction.x = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.y = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	// 교수님 코드 참고
	// printf("%f, %f \n", Direction.x, Direction.y);
	Direction.Nomalize();

	if (Teamflag == Red)
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
}

Character::~Character()
{
}

bool Character::CreateArrow(DWORD time)
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

void Character::Render(Renderer * renderer)
{
	renderer->DrawSolidRect(Position.x, Position.y, 0.0f, Size, Color.r, Color.g, Color.b, Color.a);
}

void Character::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	Position.x += Direction.x * Speed * s ;
	Position.y += Direction.y * Speed * s ;

	if (Position.x <= -WindowWidth/2 + Size / 2 || Position.x >= WindowWidth/2 - Size / 2)
		Direction.x = Direction.x * -1;
	if (Position.y <= -WindowHeight/2 + Size / 2 || Position.y >= WindowHeight/2 - Size / 2)
		Direction.y = Direction.y * -1;

	LifeTime -= 0.1f;
}
