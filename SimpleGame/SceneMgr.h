#pragma once
#include <cstdlib>
#include <ctime>
#include <windows.h>
//
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
//
#include "Object.h"
#include "Renderer.h"
#include "LoadPng.h"
#include "Mydefine.h"
//
#include "Building.h"
#include "Character.h"
#include "Bullet.h"
#include "Arrow.h"
//
#define MAX_OBJECTS_COUNT 200
//

class SceneMgr
{
private:
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;
	GLuint mBackGround;
	float RedCharacterTimer;
	float BlueCharacterTimer;
	bool CreateBlueCharacter;
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
	void CreateBulletArrow(DWORD time);
	void AddObject(float x, float y, Type ObjectType, Object* Parent, Team flag);
	void DeleteBulletArrow();
	void CreateCharacterRed(DWORD time);
	void CreateCharacterBlue(DWORD time);
};