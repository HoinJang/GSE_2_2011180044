#include "stdafx.h"
#include "Character.h"


Character::Character(const float x, const float y, const int type, Team flag) : Object(x, y, type, flag)
{
	Size = 30.0f;
	Speed = 300.0f;
	LifeTime = 10000.0f;
	Life = 100.0f;

	Direction.x = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.y = (((float)std::rand() / (float)RAND_MAX) - 0.5f);
	Direction.Nomalize();

	Color.r = 1.0f;
	Color.g = 1.0f;
	Color.b = 1.0f;
	Color.a = 1.0f;
	ParentNode = NULL;

	c_texture = 0;
	spriteX = 0;
	spriteTime = 0;
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

	if (c_texture == 0)
	{
		if (Teamflag == Red)
		{
			c_texture = renderer->CreatePngTexture("./Resources/Red.png");
		}
		else
		{
			c_texture = renderer->CreatePngTexture("./Resources/Blue.png");
		}
	}
	renderer->DrawTexturedRectSeq(Position.x, Position.y, 0.0, Size + 20, Color.r, Color.g, Color.b, Color.a, c_texture, spriteX, 0,3,1, LEVEL_SKY);

	if (Teamflag == Red)
		renderer->DrawSolidRectGauge(Position.x, Position.y + Size , 0.0f, Size , LIFEGAUGESIZE,
			1.0f, 0.0f, 0.0f, 1.0f, Life / CHARACTERLIFE, LEVEL_GROUND);
	else
		renderer->DrawSolidRectGauge(Position.x, Position.y + Size, 0.0f, Size , LIFEGAUGESIZE,
			0.0f, 0.0f, 1.0f, 1.0f, Life / CHARACTERLIFE, LEVEL_GROUND);
	renderer->DrawTextW(Position.x-Size/2, Position.y - Size, GLUT_BITMAP_HELVETICA_10, 0, 0, 0, "Character");
}

void Character::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	spriteTime += 1;

	Position.x += Direction.x * Speed * s ;
	Position.y += Direction.y * Speed * s ;

	if (Position.x <= -WindowWidth/2 + Size / 2 || Position.x >= WindowWidth/2 - Size / 2)
		Direction.x = Direction.x * -1;
	if (Position.y <= -WindowHeight/2 + Size / 2 || Position.y >= WindowHeight/2 - Size / 2)
		Direction.y = Direction.y * -1;

	LifeTime -= 0.1f;
	
	if (spriteTime > 200)
	{
		spriteX += 1;
		spriteTime = 0;
	}
	if (spriteX == 2)
	{
		spriteX = 0;
	}
}
