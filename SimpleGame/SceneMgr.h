#pragma once

#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Object.h"
#include "Renderer.h"

#include "Building.h"
#include "Character.h"
#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
public:
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;
	int Character_num;
	float CreateBulletTimer;
public:
	SceneMgr();
	~SceneMgr();
	void Init();
	void Destory();
	void Render();
	void Update(DWORD time);
	void MouseInput(int button, int state, int x, int y);
private:
	bool CollisionCheck(float x1, float y1, float x2, float y2, float size1, float size2);
	void LifeAndLifeTimeCheck();
	void CollisionObjectCheck();
};