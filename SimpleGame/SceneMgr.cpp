#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;

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
		m_objects[i]->setColor(0, 0, 0);
		m_objects[i]->setSpeed(1, 1, 1);
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

void SceneMgr::SceneUpdate()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update();
	}
}

void SceneMgr::CollisionCheck()
{
}
