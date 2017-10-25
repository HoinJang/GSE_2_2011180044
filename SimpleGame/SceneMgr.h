#pragma once

#include "Object.h"
#include "Renderer.h"
#include <cstdlib>
#include <ctime>

#define MAX_OBJECTS_COUNT 20

class SceneMgr
{
public:
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;
public:
	SceneMgr(int x, int y);
	~SceneMgr();

	void Init();
	void Destory();
	void Render();

	void SceneUpdate(DWORD time); 
	bool CollisionCheck(float x1, float y1, float x2, float y2, float size);
	void TestCollision();
};