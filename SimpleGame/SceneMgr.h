#pragma once

#include "Object.h"
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
	void SceneUpdate();
	void CollisionCheck();
};