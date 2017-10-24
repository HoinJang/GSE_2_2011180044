#pragma once

#include "Object.h"
#include "Renderer.h"
#include <cstdlib>
#include <ctime>

#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
public:
	Object *m_objects[MAX_OBJECTS_COUNT];
public:
	SceneMgr();
	~SceneMgr();

	void Init();
	void Destory();

	void SceneUpdate();
	void CollisionCheck();
};