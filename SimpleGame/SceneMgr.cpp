#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	m_renderer = NULL;
	Character_num = 0;
	CreateBulletTimer = 0.0f;

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
	m_renderer = new Renderer(500, 500);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_objects[0] = new Building(0, 0, 0, BUILDING);
	Character_num = 0;
	CreateBulletTimer = 0.0f;
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
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			m_objects[i]->Render(m_renderer);
		}
	}
}

void SceneMgr::Update(DWORD time)
{
	float s = (float)time / 1000.0f;
	CreateBulletTimer += s;
	if (CreateBulletTimer > 0.5f)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		{
			if (m_objects[i] == NULL)
			{
				m_objects[i] = new Bullet(0, 0, 0, BULLET);
				break;
			}
		}
		CreateBulletTimer = 0.0f;
	}

	//
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	}
	LifeAndLifeTimeCheck();
	CollisionObjectCheck();


}

void SceneMgr::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			{
				if (m_objects[i] == NULL && Character_num < 10)
				{
					m_objects[i] = new Character((float)(x-250), (float)(250-y), 0.0f, CHARACTER);
					Character_num++;
					break;
				}
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
			if (m_objects[i]->GetType() == CHARACTER)
				Character_num--;
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
			if (CollisionCheck(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[j]->GetPositionX(), m_objects[j]->GetPositionY(), m_objects[i]->GetSize(), m_objects[j]->GetSize()))
			{
				if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == CHARACTER))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
					Character_num--;
				}
				else if ((m_objects[i]->GetType() == CHARACTER) && (m_objects[j]->GetType() == BULLET))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				break;
			}
		}
	}
}
