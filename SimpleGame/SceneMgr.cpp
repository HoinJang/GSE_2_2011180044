#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::SceneUpdate()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		m_objects[i]->Update();
	}
}

void SceneMgr::CollisionCheck()
{
}
