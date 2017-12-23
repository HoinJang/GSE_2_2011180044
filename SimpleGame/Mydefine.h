#pragma once
#define WindowWidth 500
#define WindowHeight 900

#define GameFieldAdjust 50
#define GameField 800

#define MAX_OBJECTS_COUNT 100

#define ARROWTIMER 3.0f
#define BULLETTIMER 3.0f

#define ARROWBULLETSIZE 20
#define LIFEGAUGESIZE 5
#define ElixirMax 10


// 낮을 수록 뒤에 Render
#define LEVEL_GOD 0.0
#define LEVEL_CLIMATE 0.1
#define LEVEL_BULLETARROW 0.2
#define LEVEL_SKY 0.3
#define LEVEL_ONGROUND 0.4
#define LEVEL_GROUND 0.5
#define LEVEL_BACKGROUND 0.9

// 오브젝트들의 체력
#define BUILDINGLIFE 800.0
#define CHARACTERLIFE1 50.0
#define CHARACTERLIFE2 200.0
#define CHARACTERLIFE3 50.0


#define ARROWBULLETLIFE 50.0


enum Type
{
	NOTSELECT = 0,
	BUILDING,
	CHARACTER_1,
	CHARACTER_2,
	CHARACTER_3,
	BULLET,
	ARROW
};
enum Team
{
	Red = 0,
	Blue
};