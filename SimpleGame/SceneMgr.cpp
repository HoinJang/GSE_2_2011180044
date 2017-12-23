#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	m_renderer = NULL;
	m_sound = NULL;
}
SceneMgr::~SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i] != NULL)
			delete m_objects[i];
	}
	delete m_renderer;
}
void SceneMgr::Init()
{
	m_sound = new Sound();
	mSound = m_sound->CreateSound("./Dependencies/SoundSamples/ophelia.mp3");
	m_sound->PlaySoundW(mSound, true, 0.2f);

	m_renderer = new Renderer(WindowWidth, WindowHeight);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	//Character Texture Init
	BlueCharacter_01_tex = m_renderer->CreatePngTexture("./Resources/Red_C_2.png");
	RedCharacter_01_tex = m_renderer->CreatePngTexture("./Resources/Blue_C_2.png");

	//Bullet Texture Init
	BulletPaticle_tex = m_renderer->CreatePngTexture("./Resources/Particle.png");

	//Red Texture Init
	BlueBuilding_tex = m_renderer->CreatePngTexture("./Resources/Building_Blue.png");
	RedBuilding_tex = m_renderer->CreatePngTexture("./Resources/Building_Red.png");


	mBackGround = m_renderer->CreatePngTexture("./Resources/BackGround.png");
	mParticleCloud = m_renderer->CreatePngTexture("./Resources/SnowTexture.png");


	ClimateTimer = 0.0f;
	RedCharacterTimer = 5.0f;
	BlueCharacterTimer = 7.0f;
	CreateBlueCharacter = false;

	AddObject(0, WindowHeight/2 - 80, BUILDING, NULL, Red);
	AddObject(-140, WindowHeight / 2 - 100, BUILDING, NULL, Red);
	AddObject(140, WindowHeight / 2 - 100, BUILDING, NULL, Red);

	AddObject(0, -WindowHeight / 2 + 100, BUILDING, NULL, Blue);
	AddObject(-140, -WindowHeight / 2 + 150, BUILDING, NULL, Blue);
	AddObject(140, -WindowHeight / 2 + 150, BUILDING, NULL, Blue);
}
void SceneMgr::Destory() 
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			delete m_objects[i];
		}
	}
	delete m_renderer;
}
void SceneMgr::Render()
{
	//배경 랜더링
	m_renderer->DrawTexturedRectXY(0.0, 0.0, 0.0, WindowWidth,WindowHeight, 1.0, 1.0, 1.0, 1.0, mBackGround, LEVEL_BACKGROUND);
	//기후 랜더링
	m_renderer->DrawParticleClimate(0.0, 0.0, 0.0, 3, 1, 1, 1, 1, -0.1, -0.1, mParticleCloud, ClimateTimer, LEVEL_GOD);
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->GetType() == CHARACTER)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
				{
					m_renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0, m_objects[i]->GetSize() + 20, 1.0f, 1.0f, 1.0f, 1.0f, BlueCharacter_01_tex, m_objects[i]->GetSpriteX(), 0, 3, 1, LEVEL_SKY);
				}
				else if (m_objects[i]->GetTeamFlag() == Blue)
				{
					m_renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0, m_objects[i]->GetSize() + 20, 1.0f, 1.0f, 1.0f, 1.0f, RedCharacter_01_tex, m_objects[i]->GetSpriteX(), 0, 3, 1, LEVEL_SKY);
				}
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + m_objects[i]->GetSize(), 0.0f, m_objects[i]->GetSize(), LIFEGAUGESIZE, m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, m_objects[i]->GetLife() / CHARACTERLIFE, LEVEL_GROUND);
			}
			else if (m_objects[i]->GetType() == BUILDING)
			{

				if (m_objects[i]->GetTeamFlag() == Red)
				{
					m_renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0, m_objects[i]->GetSize() + 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, RedBuilding_tex, LEVEL_GROUND);
				}
				else if (m_objects[i]->GetTeamFlag() == Blue)
				{
					m_renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0, m_objects[i]->GetSize() + 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, BlueBuilding_tex, LEVEL_GROUND);
				}
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + m_objects[i]->GetSize() / 2, 0.0f, m_objects[i]->GetSize() / 2, LIFEGAUGESIZE, m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, m_objects[i]->GetLife() / BUILDINGLIFE, LEVEL_GROUND);
			}
			else if(m_objects[i]->GetType() == BULLET)
			{
				m_renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen() + 0.5f, m_objects[i]->GetColorBlue(), 1.0f, -m_objects[i]->GetDirectionX(), -m_objects[i]->GetDirectionY(), BulletPaticle_tex, m_objects[i]->GetParticleTime(), LEVEL_BULLETARROW);
			}
			else if (m_objects[i]->GetType() == ARROW)
			{

				m_renderer->DrawSolidRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen() + 0.5f, m_objects[i]->GetColorBlue(), 1.0f, LEVEL_BULLETARROW);
			}
		}
	}

}
void SceneMgr::Update(DWORD time)
{
	float s = (float)time / 1000.0f;
	ClimateTimer += s;

	CreateBulletArrow(time);
	CreateCharacterRed(time);
	CreateCharacterBlue(time);
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	}
	CollisionObjectCheck();
	LifeAndLifeTimeCheck();
	DeleteBulletArrow();
}
void SceneMgr::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			if ((y > WindowHeight / 2) && CreateBlueCharacter)
			{
				AddObject((float)(x - (WindowWidth / 2)), (float)((WindowHeight / 2)-y), CHARACTER, NULL, Blue);
				BlueCharacterTimer = 0.0f;
				CreateBlueCharacter = false;
			}
		}
	}
}
bool SceneMgr::CollisionCheck(float x1, float y1, float x2, float y2,  float size1 , float size2)
{
	if (x1 - size1 / 2 > x2 + size2 / 2)
		return false;
	if (x1 + size1 / 2 < x2 - size2 / 2)
		return false;
	if (y1 + size1 / 2 < y2 - size2 / 2)
		return false;
	if (y1 - size1 / 2 > y2 + size2 / 2)
		return false;

	return true;
}
void SceneMgr::LifeAndLifeTimeCheck()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
			continue;
		if ((m_objects[i]->GetLife() <= 0.0f) || (m_objects[i]->GetLifeTime() <= 0.0f))
		{
			delete m_objects[i];
			m_objects[i] = NULL;
		}
	}
}
void SceneMgr::CollisionObjectCheck()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT ; j++)
		{
			if ((m_objects[i] == NULL) || m_objects[j] == NULL) continue;
			if (i == j) continue;
			if (m_objects[i]->GetTeamFlag() == m_objects[j]->GetTeamFlag()) continue;
			if (CollisionCheck(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[j]->GetPositionX(), m_objects[j]->GetPositionY(), m_objects[i]->GetSize(), m_objects[j]->GetSize()))
			{
				if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == CHARACTER ))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == BULLET))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == ARROW))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == CHARACTER) && (m_objects[j]->GetType() == BULLET))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == CHARACTER) && (m_objects[j]->GetType() == ARROW))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
			}
		}
	}
}
void SceneMgr::CreateBulletArrow(DWORD time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i]->GetType() == BUILDING)
		{
			if (((Building*)m_objects[i])->CreateBullet(time))
			{
				AddObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), BULLET, m_objects[i],m_objects[i]->GetTeamFlag());
			}
		}
		else if (m_objects[i]->GetType() == CHARACTER)
		{
			if (((Character*)m_objects[i])->CreateArrow(time))
			{
				AddObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), ARROW, m_objects[i], m_objects[i]->GetTeamFlag());
			}
		}
	}
}
void SceneMgr::AddObject(float x, float y, Type ObjectType, Object* Parent, Team flag)
{

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			continue;
		if (ObjectType == BUILDING)
		{
			m_objects[i] = new Building(x, y, ObjectType, flag);
			break;
		}
		else if (ObjectType == CHARACTER)
		{
			m_objects[i] = new Character(x, y, ObjectType, flag);
			break;
		}
		else if (ObjectType == BULLET)
		{
			m_objects[i] = new Bullet(x, y, ObjectType, flag);
			m_objects[i]->setParentNode(Parent);
			break;
		}
		else if (ObjectType == ARROW)
		{
			m_objects[i] = new Arrow(x, y, ObjectType, flag);
			m_objects[i]->setParentNode(Parent);
			break;
		}
	}
}
void SceneMgr::DeleteBulletArrow()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i]->GetType() == ARROW)
		{
			if (((Arrow*)m_objects[i])->GetErase())
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
		else if (m_objects[i]->GetType() == BULLET)
		{
			if (((Bullet*)m_objects[i])->GetErase())
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}
}
void SceneMgr::CreateCharacterRed(DWORD time)
{
	float sec = time / 1000.0f;
	RedCharacterTimer += sec;
	if (RedCharacterTimer >= 5.0f)
	{
		AddObject((float)((rand() % WindowWidth) - 200), (float)(rand() % (WindowHeight/2) ), CHARACTER, NULL, Red);
		RedCharacterTimer = 0.0f;
	}
}
void SceneMgr::CreateCharacterBlue(DWORD time)
{
	float sec = time / 1000.0f;
	BlueCharacterTimer += sec;
	if (BlueCharacterTimer >= 7.0f)
	{
		CreateBlueCharacter = true;
	}
}
