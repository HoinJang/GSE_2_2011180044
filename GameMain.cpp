#include "GameMain.h"
#include "stdafx.h"
GameMain::GameMain()
{
	Entry(MENU, new Menu);
	Trans(MENU);
}
GameMain::~GameMain()
{

}