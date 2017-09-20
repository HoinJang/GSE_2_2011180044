#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{if(p) {delete (p);     (p)=nullptr;}}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)			{if(p) {delete[] (p);     (p)=nullptr;}}
#endif

enum GAMESTATE
{
	MENU = 0,
	GAME,
	SELECT,
};