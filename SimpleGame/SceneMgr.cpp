#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	m_renderer = NULL;
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
}

void SceneMgr::Destory() 
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			delete m_objects[i];
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
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	}
	LifeAndLifeTimeCheck();
}

void SceneMgr::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Character((float)(x-250), (float)(250-y), 0.0f, CHARACTER);
					break;
				}
			}
		}
	}


}

bool SceneMgr::CollisionCheck(float x1, float y1, float x2, float y2,  float size)
{
	if (x1 - size / 2 > x2 + size / 2)
		return false;
	if (x1 + size / 2 < x2 - size / 2)
		return false;
	if (y1 + size / 2 < y2 - size / 2)
		return false;
	if (y1 - size / 2 > y2 + size / 2)
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


void SceneMgr::TestCollision()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT ; j++)
		{
			if (i == j) continue;
			if (CollisionCheck(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[j]->GetPositionX(), m_objects[j]->GetPositionY(), m_objects[i]->GetSize()))
			{
				m_objects[i]->setColor(1, 0, 0);
				m_objects[j]->setColor(1, 0, 0);
				return;
			}
			else
			{
				m_objects[i]->setColor(0, 0, 1);
				m_objects[j]->setColor(0, 0, 1);
			}
		}
	}
}
