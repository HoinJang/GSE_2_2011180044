#include "Singletone.h"
#include "Menu.h"
#include "SceneManager.h"
#include "myDefine.h"
#include "myInclude.h"
#include "stdafx.h"

class GameMain : public Singletone<GameMain>, public SceneManager
{
public:
	GameMain();
	~GameMain();
public:
};
