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
#include "MyDefine.h"
#include "Sound.h"
//
#include "Building.h"
#include "Character_Type1.h"
#include "Character_Type2.h"
#include "Character_Type3.h"
#include "Bullet.h"
#include "Arrow.h"



class SceneMgr
{
private:
	Object *m_objects[MAX_OBJECTS_COUNT];
	Renderer *m_renderer;
	Sound *m_sound;
private:
	GLuint mSound;
	GLuint mBackGround;
	GLuint mParticleCloud;
	GLuint mParticleFire;
	GLuint mParticleFlower;
private:
	GLuint BlueCharacter_01_tex;
	GLuint RedCharacter_01_tex;
	GLuint BlueCharacter_02_tex;
	GLuint RedCharacter_02_tex;
	GLuint BlueCharacter_03_tex;
	GLuint RedCharacter_03_tex;
	GLuint BulletPaticle_tex;
	GLuint AttackPaticle_tex;
	GLuint BlueBuilding_tex;
	GLuint RedBuilding_tex;
	GLuint UI_Box_tex;
private:
	GLuint Win_tex;
	GLuint Lose_tex;
private:
	Type SelectCharacter;
	float MyElixir;
	float ComElixir;
	bool DrawBorder;
private:
	float RedCharacterTimer;
	float ClimateTimer;
	TeamObjectNum RedNum;
	TeamObjectNum BlueNum;
	bool GameEnd;
	bool Win;
	bool Lose;
public:
	SceneMgr();
	~SceneMgr();
	void Init();
	void Destory();
	void Render();
	void Update(DWORD time);
	void MouseInput(int button, int state, int x, int y);
	void KeyInput(unsigned char key, int x, int y);
private:
	bool CollisionCheck(float x1, float y1, float x2, float y2, float size1, float size2);
	void LifeAndLifeTimeCheck();
	void CollisionObjectCheck();
	void CreateBullet(DWORD time);
	void AddObject(float x, float y, Type ObjectType, Object* Parent, Team flag);
	void DeleteBulletArrow();
	void CreateCharacterRed();
private:
	void SetAICharacter01();
	void SetAICharacter02();
	void SetAICharacter03(DWORD time);
private:
	void UpdateObjectNum();
	void GameEndCheck();
};