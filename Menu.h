#pragma once
#include "MyDefine.h"
#include "MyInclude.h"
#include "Scene.h"
#include "stdafx.h"

class Menu : public Scene
{
public:
	Menu();
	~Menu();
public:
	void Init();
	void Destroy();
	void Update();
	void Render();
	bool KeyBoard();
};