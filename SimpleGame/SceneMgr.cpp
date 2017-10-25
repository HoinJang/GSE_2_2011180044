#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr(int x, int y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	//
	m_renderer = new Renderer(x, y);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_objects[i] != NULL)
			delete m_objects[i];
		}
}

void SceneMgr::Init()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = new Object();
		m_objects[i]->setPosition((float)(rand() % 500 - 250), (float)(rand() % 500 - 250), 1.0);
		m_objects[i]->setColor(1, 1, 1);
		m_objects[i]->setDirection((rand()%20+1 - 10)*0.1, (rand() % 20 + 1 - 10)*0.1, 1);
		m_objects[i]->setSpeed(rand() % 2 + 1);
		m_objects[i]->setSize(20.0);
	}
}

void SceneMgr::Destory() 
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			delete m_objects[i];
	}
}

void SceneMgr::Render()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			//m_renderer->DrawSolidRect(m_objects[i]->GetPositionX(),m_objects[i]->GetPositionY(),m_objects[i]->GetPositionZ(),m_objects[i]->GetSize(), m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1);
			m_objects[i]->Render(m_renderer);
		}
	}
}

void SceneMgr::SceneUpdate(DWORD time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	}
	TestCollision();
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
