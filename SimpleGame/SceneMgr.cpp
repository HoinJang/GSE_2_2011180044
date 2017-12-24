#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	m_renderer = NULL;
	m_sound = NULL;
}
SceneMgr::~SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i] != NULL)
			delete m_objects[i];
	}
	delete m_renderer;
	delete m_sound;
}
void SceneMgr::Init()
{
	SelectCharacter = NOTSELECT;
	m_renderer = new Renderer(WindowWidth, WindowHeight);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_sound = new Sound();
	mSound = m_sound->CreateSound("./Resources/BackGroundSound.wav");
	mCharacterInitSound = m_sound->CreateSound("./Resources/CharacterInitSound1.wav");
	mCollisionSound = m_sound->CreateSound("./Resources/CollisionSound.wav");
	mCharacterInitSound2 = m_sound->CreateSound("./Resources/CharacterInitSound2.wav");
	mCharacterInitSound3 = m_sound->CreateSound("./Resources/CharacterInitSound3.wav");
	//Sound Start
	m_sound->PlaySoundW(mSound, true, 0.5f);
	//Character Texture Init
	BlueCharacter_01_tex = m_renderer->CreatePngTexture("./Resources/Blue_C_1.png");
	RedCharacter_01_tex = m_renderer->CreatePngTexture("./Resources/Red_C_1.png");
	BlueCharacter_02_tex = m_renderer->CreatePngTexture("./Resources/Blue_C_2.png");
	RedCharacter_02_tex = m_renderer->CreatePngTexture("./Resources/Red_C_2.png");
	BlueCharacter_03_tex = m_renderer->CreatePngTexture("./Resources/Blue_C_3.png");
	RedCharacter_03_tex = m_renderer->CreatePngTexture("./Resources/Red_C_3.png");
	//Bullet Texture Init
	BulletPaticle_tex = m_renderer->CreatePngTexture("./Resources/Particle_1.png");
	AttackPaticle_tex = m_renderer->CreatePngTexture("./Resources/Particle_3.png");
	//Building Texture Init
	BlueBuilding_tex = m_renderer->CreatePngTexture("./Resources/Building_Blue.png");
	RedBuilding_tex = m_renderer->CreatePngTexture("./Resources/Building_Red.png");
	//BackGround Texture Init
	mBackGround = m_renderer->CreatePngTexture("./Resources/BackGround.png");
	//Particle Texture Init
	mParticleCloud = m_renderer->CreatePngTexture("./Resources/SnowTexture.png");
	mParticleFire = m_renderer->CreatePngTexture("./Resources/FireTexture.png");
	mParticleFlower = m_renderer->CreatePngTexture("./Resources/FlowerTexture.png");
	//UI Texture Init
	UI_Box_tex = m_renderer->CreatePngTexture("./Resources/UI_Box.png");
	//End Texture Init
	Win_tex = m_renderer->CreatePngTexture("./Resources/End_Win.png");
	Lose_tex = m_renderer->CreatePngTexture("./Resources/End_Lose.png");
	//
	ComElixir = 0.0f;
	MyElixir = 0.0f;
	ClimateTimer = 0.0f;
	RedCharacterTimer = 5.0f;
	DrawBorder = false;
	RedNum = { 0,0,0,0 };
	BlueNum = { 0,0,0,0 };
	GameEnd = false;
	Win = false;
	Lose = false;
	AddObject(0, GameField/2 - 60, BUILDING, NULL, Red);
	AddObject(-135, GameField / 2 - 100, BUILDING, NULL, Red);
	AddObject(135, GameField / 2 - 100, BUILDING, NULL, Red);

	AddObject(0, -GameField / 2 + 100, BUILDING, NULL, Blue);
	AddObject(-135, -GameField / 2 + 150, BUILDING, NULL, Blue);
	AddObject(135, -GameField / 2 + 150, BUILDING, NULL, Blue);
}
void SceneMgr::Destory() 
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			delete m_objects[i];
			m_objects[i] = NULL;
		}
	}
	m_renderer->DeleteTexture(Lose_tex);
	m_renderer->DeleteTexture(Win_tex);
	m_renderer->DeleteTexture(UI_Box_tex);
	m_renderer->DeleteTexture(mParticleFlower);
	m_renderer->DeleteTexture(mParticleFire);
	m_renderer->DeleteTexture(mParticleCloud);
	m_renderer->DeleteTexture(mBackGround);
	m_renderer->DeleteTexture(RedBuilding_tex);
	m_renderer->DeleteTexture(BlueBuilding_tex);
	m_renderer->DeleteTexture(AttackPaticle_tex);
	m_renderer->DeleteTexture(BulletPaticle_tex);
	m_renderer->DeleteTexture(RedCharacter_03_tex);
	m_renderer->DeleteTexture(BlueCharacter_03_tex);
	m_renderer->DeleteTexture(RedCharacter_02_tex);
	m_renderer->DeleteTexture(BlueCharacter_02_tex);
	m_renderer->DeleteTexture(RedCharacter_01_tex);
	m_renderer->DeleteTexture(BlueCharacter_01_tex);
	m_sound->DeleteSound(mSound);
	m_renderer = NULL;
	m_sound = NULL;
}
void SceneMgr::Render()
{
	// UIBOX 랜더링
	m_renderer->DrawTexturedRectXY(0.0f, -GameField/2, 0.0, WindowWidth, 100.0f, 1.0, 1.0, 1.0, 1.0, UI_Box_tex, LEVEL_GOD);
	// 엘릭서
	m_renderer->DrawSolidRectGauge(125.0f, -GameField/2, 0.0f, WindowWidth/2, 100.0f, 0.9f, 0.3f, 0.9f, 1.0f, MyElixir/ElixirMax, LEVEL_GOD);
	// 배경 랜더링
	m_renderer->DrawTexturedRectXY(0.0, GameFieldAdjust, 0.0, WindowWidth, GameField, 1.0, 1.0, 1.0, 1.0, mBackGround, LEVEL_BACKGROUND);
	// 기후 랜더링
	if(!GameEnd)
		m_renderer->DrawParticleClimate(0.0, 100, 0.0, 3, 1, 1, 1, 1, -0.1, -0.1, mParticleCloud, ClimateTimer, LEVEL_CLIMATE);
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->GetType() == CHARACTER_1)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
				{
					m_renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), 1.0f, 1.0f, 1.0f, 1.0f, RedCharacter_01_tex, m_objects[i]->GetSpriteX(), 0, 4, 1, LEVEL_ONGROUND);
				}
				else if (m_objects[i]->GetTeamFlag() == Blue)
				{
					m_renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), 1.0f, 1.0f, 1.0f, 1.0f, BlueCharacter_01_tex, m_objects[i]->GetSpriteX(), 0, 4, 1, LEVEL_ONGROUND);
				}
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust + m_objects[i]->GetSize()/2, 0.0f, m_objects[i]->GetSize(), LIFEGAUGESIZE, m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, m_objects[i]->GetLife() / CHARACTERLIFE1, LEVEL_ONGROUND);
				if(DrawBorder) 
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize() , m_objects[i]->GetSize(), 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
			}
			else if (m_objects[i]->GetType() == CHARACTER_2)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
				{
					m_renderer->DrawTexturedRectSeqXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize() * 2, m_objects[i]->GetSize(), 1.0f, 1.0f, 1.0f, 1.0f, RedCharacter_02_tex, m_objects[i]->GetSpriteX(), 0, 3, 1, LEVEL_SKY);
					if (((Character_T2*)m_objects[i])->GetAttack() == true)
					{
						m_renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust - m_objects[i]->GetSize(), 0.0f, m_objects[i]->GetSize() / 2, 0.9f, 0.3f, 0.3f, 1.0f, 0.0f, -0.5f, mParticleFire, m_objects[i]->GetParticleTime(), LEVEL_BULLETARROW);
					}
				}
				else if (m_objects[i]->GetTeamFlag() == Blue)
				{
					m_renderer->DrawTexturedRectSeqXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize() * 2, m_objects[i]->GetSize(), 1.0f, 1.0f, 1.0f, 1.0f, BlueCharacter_02_tex, m_objects[i]->GetSpriteX(), 0, 3, 1, LEVEL_SKY);
					if (((Character_T2*)m_objects[i])->GetAttack() == true)
					{
						m_renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust + m_objects[i]->GetSize(), 0.0f, m_objects[i]->GetSize()/2 , 0.9f, 0.3f, 0.3f, 1.0f, 0.0f , 0.5f , mParticleFire, m_objects[i]->GetParticleTime(), LEVEL_BULLETARROW);
					}
				}
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust + m_objects[i]->GetSize()/2, 0.0f, m_objects[i]->GetSize(), LIFEGAUGESIZE, m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, m_objects[i]->GetLife() / CHARACTERLIFE2, LEVEL_SKY);
				if (DrawBorder)
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetSize(), 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
			}
			else if (m_objects[i]->GetType() == CHARACTER_3)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
				{
					m_renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), 1.0f, 1.0f, 1.0f, 1.0f, RedCharacter_03_tex, m_objects[i]->GetSpriteX(), 0, 7, 1, LEVEL_ONGROUND);
				}
				else if (m_objects[i]->GetTeamFlag() == Blue)
				{
					m_renderer->DrawTexturedRectSeq(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), 1.0f, 1.0f, 1.0f, 1.0f, BlueCharacter_03_tex, m_objects[i]->GetSpriteX(), 0, 7, 1, LEVEL_ONGROUND);
				}
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust + m_objects[i]->GetSize() / 2, 0.0f, m_objects[i]->GetSize(), LIFEGAUGESIZE, m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, m_objects[i]->GetLife() / CHARACTERLIFE3, LEVEL_ONGROUND);
				if (DrawBorder)
				{
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetSize(), 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, CHARACTER3_BORDER, CHARACTER3_BORDER, 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
				}
			}
			else if (m_objects[i]->GetType() == BUILDING)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
				{
					m_renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize() + 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, RedBuilding_tex, LEVEL_GROUND);
				}
				else if (m_objects[i]->GetTeamFlag() == Blue)
				{
					m_renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize() + 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, BlueBuilding_tex, LEVEL_GROUND);
				}
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust + m_objects[i]->GetSize() / 2, 0.0f, m_objects[i]->GetSize() / 2, LIFEGAUGESIZE, m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, m_objects[i]->GetLife() / BUILDINGLIFE, LEVEL_GROUND);
				if (DrawBorder)
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetSize(), 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
			}
			else if(m_objects[i]->GetType() == BULLET)
			{
				m_renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen() + 0.5, m_objects[i]->GetColorBlue(), 1.0f, -m_objects[i]->GetDirectionX(), -m_objects[i]->GetDirectionY(), BulletPaticle_tex, m_objects[i]->GetParticleTime(), LEVEL_BULLETARROW);
				if (DrawBorder)
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetSize(), 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
			}
			else if (m_objects[i]->GetType() == ARROW)
			{
				m_renderer->DrawParticle(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 1.0f, -m_objects[i]->GetDirectionX(), -m_objects[i]->GetDirectionY(), BulletPaticle_tex, m_objects[i]->GetParticleTime(), LEVEL_BULLETARROW);
				if (DrawBorder)
					m_renderer->DrawBorderXY(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY() + GameFieldAdjust, 0.0f, m_objects[i]->GetSize(), m_objects[i]->GetSize(), 0.0f, 0.0f, 0.0f, 1.0f, LEVEL_GOD);
			}
		}
	}
	m_renderer->DrawTextW(80 , -400, GLUT_BITMAP_HELVETICA_18, 0.0f, 0.0f, 0.0f, "Elixer(Max : 10)");
	if (Win)
	{
		m_renderer->DrawTexturedRectXY(0.0f, 0.0, 0.0, WindowWidth, 200.0f, 1.0, 1.0, 1.0, 1.0, Win_tex, LEVEL_GOD);
		m_renderer->DrawParticleClimate(0.0, 100, 0.0, 3, 1, 1, 1, 1, -0.1, -0.1, mParticleFlower, ClimateTimer, LEVEL_CLIMATE);
	}
	if (Lose)
	{
		m_renderer->DrawTexturedRectXY(0.0f, 0.0, 0.0, WindowWidth, 200.0f, 1.0, 1.0, 1.0, 1.0, Lose_tex, LEVEL_GOD);
		m_renderer->DrawParticleClimate(0.0, 100, 0.0, 3, 1, 1, 1, 1, -0.1, -0.1, mParticleFire, ClimateTimer, LEVEL_CLIMATE);
	}
}
void SceneMgr::Update(DWORD time)
{
	float s = (float)time / 1000.0f;

	ClimateTimer += s;

	if (!GameEnd)
	{
		MyElixir += s;
		MyElixir = (float)min(MyElixir, 10.0);
		ComElixir += 1.5 * s;
		ComElixir = (float)min(ComElixir, 10.0);
		// 엘릭서 제한
		SetAICharacter01();
		SetAICharacter02();
		CollisionObjectCheck();
		SetAICharacter03(time);
		CreateBullet(time);
		UpdateObjectNum();
		CreateCharacterRed();
		LifeAndLifeTimeCheck();
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_objects[i] != NULL)
				m_objects[i]->Update(time);
		}
		DeleteBulletArrow();
		GameEndCheck();
	}
}
void SceneMgr::MouseInput(int button, int state, int x, int y)
{

	if (GameEnd)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				if ((y > GameField / 2 && y < GameField))
				{	
					Destory();
					Init();
				}
			}
		}
	}
	else
	{
		//cout << x << " " << y << endl;
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				if (x >= 0 && x <= 80 && y <= WindowHeight && y >= GameField)
				{
					SelectCharacter = CHARACTER_1;
				}
				else if (x >= 80 && x <= 160 && y <= WindowHeight && y >= GameField)
				{
					SelectCharacter = CHARACTER_2;
				}
				else if (x >= 160 && x <= 240 && y <= WindowHeight && y >= GameField)
				{
					SelectCharacter = CHARACTER_3;
				}
			}
		}

		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				if ((y > GameField / 2 && y < GameField))
				{
					if (SelectCharacter == CHARACTER_1 && MyElixir > 3)
					{
						m_sound->PlaySoundW(mCharacterInitSound, false, 0.7f);
						AddObject((float)(x - (WindowWidth / 2)), (float)((GameField / 2) - y), CHARACTER_1, NULL, Blue);
						MyElixir -= 3;
					}
					else if (SelectCharacter == CHARACTER_2 && MyElixir > 7)
					{
						m_sound->PlaySoundW(mCharacterInitSound2, false, 0.7f);
						AddObject((float)(x - (WindowWidth / 2)), (float)((GameField / 2) - y), CHARACTER_2, NULL, Blue);
						MyElixir -= 7;
					}
					else if (SelectCharacter == CHARACTER_3 && MyElixir > 5)
					{
						m_sound->PlaySoundW(mCharacterInitSound3, false, 0.7f);
						AddObject((float)(x - (WindowWidth / 2)), (float)((GameField / 2) - y), CHARACTER_3, NULL, Blue);
						MyElixir -= 5;
					}
				}
			}
		}
	}
}
void SceneMgr::KeyInput(unsigned char key, int x, int y)
{
	if (key == 's' || key == 'S')
	{
		if (DrawBorder)
			DrawBorder = false;
		else
			DrawBorder = true;
	}
}
void SceneMgr::LifeAndLifeTimeCheck()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
			continue;
		if ((m_objects[i]->GetLife() <= 0.0f) || (m_objects[i]->GetLifeTime() <= 0.0f))
		{
			delete m_objects[i];
			m_objects[i] = NULL;
		}
	}
}
void SceneMgr::CollisionObjectCheck()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT ; ++j)
		{
			// NULL CHECK
			if ((m_objects[i] == NULL) || m_objects[j] == NULL) continue;
			// INDEX가 같을때 CHECK
			if (i == j) continue;
			// 같은 팀일때 CHECK
			if (m_objects[i]->GetTeamFlag() == m_objects[j]->GetTeamFlag())
				continue;
			if (CollisionCheck(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[j]->GetPositionX(), m_objects[j]->GetPositionY(), m_objects[i]->GetSize(), m_objects[j]->GetSize()))
			{
				if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == CHARACTER_1))
				{
					float temp = m_objects[i]->GetLife();
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					m_objects[j]->Collision_Life(temp);
					m_sound->PlaySoundW(mCollisionSound, false, 0.5f);
				}
				else if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == CHARACTER_2))
				{
					((Character_T2*)m_objects[j])->SetAttack(true);
					m_objects[i]->Collision_Life(0.05f);
					if (m_objects[i]->GetLife() <= 0.0f)
					{
						((Character_T2*)m_objects[j])->SetAttack(false);
					}
				}
				else if ((m_objects[i]->GetType() == BUILDING) && (m_objects[j]->GetType() == ARROW))
				{
					m_objects[i]->Collision_Life(ARROWDAMAGE);
					((Character_T3*)m_objects[j]->GetParentNode())->SetMove(true);
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == CHARACTER_1) && (m_objects[j]->GetType() == ARROW))
				{
					m_objects[i]->Collision_Life(ARROWDAMAGE);
					((Character_T3*)m_objects[j]->GetParentNode())->SetMove(true);
					delete m_objects[j];
					m_objects[j] = NULL;
					m_sound->PlaySoundW(mCollisionSound, false, 0.5f);
				}
				else if ((m_objects[i]->GetType() == CHARACTER_2) && (m_objects[j]->GetType() == ARROW))
				{
					m_objects[i]->Collision_Life(ARROWDAMAGE);
					((Character_T3*)m_objects[j]->GetParentNode())->SetMove(true);
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == CHARACTER_3) && (m_objects[j]->GetType() == ARROW))
				{
					m_objects[i]->Collision_Life(ARROWDAMAGE);
					delete m_objects[j];
					m_objects[j] = NULL;

				}
				else if ((m_objects[i]->GetType() == ARROW) && (m_objects[j]->GetType() == CHARACTER_3))
				{
					m_objects[j]->Collision_Life(ARROWDAMAGE);
					delete m_objects[i];
					m_objects[i] = NULL;
				}
				else if ((m_objects[i]->GetType() == CHARACTER_1) && (m_objects[j]->GetType() == BULLET))
				{
					float temp = m_objects[i]->GetLife();
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					m_objects[j]->Collision_Life(temp);
					m_sound->PlaySoundW(mCollisionSound, false, 0.5f);
				}
				else if ((m_objects[i]->GetType() == CHARACTER_2) && (m_objects[j]->GetType() == BULLET))
				{
					float temp = m_objects[i]->GetLife();
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					m_objects[j]->Collision_Life(temp);
				}
				else if ((m_objects[i]->GetType() == CHARACTER_3) && (m_objects[j]->GetType() == BULLET))
				{
					float temp = m_objects[i]->GetLife();
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					m_objects[j]->Collision_Life(temp);
				}
			}
		}
	}
}
void SceneMgr::CreateBullet(DWORD time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i]->GetType() == BUILDING)
		{
			if (((Building*)m_objects[i])->CreateBullet(time))
			{
				AddObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), BULLET, m_objects[i],m_objects[i]->GetTeamFlag());
			}
		}
	}
}
void SceneMgr::CreateCharacterRed()
{
	int Think = 300;

	if (BlueNum.CHARACTER2_NUM > RedNum.CHARACTER2_NUM)
	{
		Think = 100;
		//cout << BlueNum.CHARACTER2_NUM << " " << RedNum.CHARACTER2_NUM << endl;
	}
	if (BlueNum.CHARACTER3_NUM > RedNum.CHARACTER3_NUM)
	{
		Think = 200;
		//cout << BlueNum.CHARACTER3_NUM << " " << RedNum.CHARACTER3_NUM << endl;
	}

	if (ComElixir >= 7.0f)
	{
		if (Think == 100)
		{
			AddObject((float)((rand() % WindowWidth) - 200), (float)(rand() % (WindowHeight / 2)), CHARACTER_2, NULL, Red);
			ComElixir -= 7.0f;
		}
		else if (Think == 200)
		{
			AddObject((float)((rand() % WindowWidth) - 200), (float)(rand() % (WindowHeight / 2)), CHARACTER_3, NULL, Red);
			ComElixir -= 5.0f;
		}
		else if (Think == 300)
		{
			ComElixir -= 3.0f;
			AddObject((float)((rand() % WindowWidth) - 200), (float)(rand() % (WindowHeight / 2)), CHARACTER_1, NULL, Red);
		}
		/*
		cout << "T" << Think << endl;
		cout << "1   " << BlueNum.CHARACTER1_NUM << " " << RedNum.CHARACTER1_NUM << endl;
		cout << "2   " << BlueNum.CHARACTER2_NUM << " " << RedNum.CHARACTER2_NUM << endl;
		cout << "3   " << BlueNum.CHARACTER3_NUM << " " << RedNum.CHARACTER3_NUM << endl;
		*/
	}
}
void SceneMgr::SetAICharacter01()
{
	//빌딩 중 가장 가까운 빌딩 찾기
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->GetType() == CHARACTER_1)
			{
				if (m_objects[i]->GetTeamFlag() == Blue)
				{
					float distance;
					float MIXdistance= 0.0f;
					int MIXindex = 0;
					if (m_objects[0] == NULL)
						break;
					for (int j = 0; j < 3; j++)
					{
						if (m_objects[j] == NULL)
							continue;
						if (m_objects[j]->GetType() != BUILDING)
							continue;
						float x = m_objects[i]->GetPositionX() - m_objects[j]->GetPositionX();
						float y = m_objects[i]->GetPositionY() - m_objects[j]->GetPositionY();
						if (j == 0)
						{
							MIXdistance = sqrt(x*x + y*y);
							MIXindex = j;
						}
						else
						{
							distance = sqrt(x*x + y*y);
							if (distance < MIXdistance)
							{
								MIXdistance = distance;
								MIXindex = j;
							}
						}
					}
					float dirx, diry;
					dirx = m_objects[MIXindex]->GetPositionX() - m_objects[i]->GetPositionX();
					diry = m_objects[MIXindex]->GetPositionY() - m_objects[i]->GetPositionY();
					m_objects[i]->setDirection(dirx, diry);
				}
				if (m_objects[i]->GetTeamFlag() == Red)
				{
					float distance;
					float MIXdistance = 0.0;
					int MIXindex = 3;
					if (m_objects[3] == NULL)
						break;
					for (int j = 3; j < 6; j++)
					{
						if (m_objects[j] == NULL)
							continue;
						if (m_objects[j]->GetType() != BUILDING)
							continue;
						float x = m_objects[i]->GetPositionX() - m_objects[j]->GetPositionX();
						float y = m_objects[i]->GetPositionY() - m_objects[j]->GetPositionY();
						if (j == 3)
						{
							MIXdistance = sqrt(x*x + y*y);
							MIXindex = j;
						}
						else
						{
							distance = sqrt(x*x + y*y);
							if (distance < MIXdistance)
							{
								MIXdistance = distance;
								MIXindex = j;
							}
						}
					}
					float dirx, diry;
					dirx = m_objects[MIXindex]->GetPositionX() - m_objects[i]->GetPositionX();
					diry = m_objects[MIXindex]->GetPositionY() - m_objects[i]->GetPositionY();
					m_objects[i]->setDirection(dirx, diry);
				}
			}
		}
	}
}
void SceneMgr::SetAICharacter02()
{
	//빌딩 중 가장 가까운 빌딩 찾기
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->GetType() == CHARACTER_2)
			{
				if (((Character_T2*)m_objects[i])->GetAttack() == true)
				{
					m_objects[i]->setDirection(0.0f, 0.0f);
					continue;
				}
				else
				{
					if (m_objects[i]->GetTeamFlag() == Blue)
					{
						float distance;
						float MIXdistance = 0.0f;
						int MIXindex = 0;
						if (m_objects[0] == NULL)
							break;
						for (int j = 0; j < 3; j++)
						{
							if (m_objects[j] == NULL)
								continue;
							if (m_objects[j]->GetType() != BUILDING)
								continue;
							float x = m_objects[i]->GetPositionX() - m_objects[j]->GetPositionX();
							float y = m_objects[i]->GetPositionY() - m_objects[j]->GetPositionY();
							if (j == 0)
							{
								MIXdistance = sqrt(x*x + y*y);
								MIXindex = j;
							}
							else
							{
								distance = sqrt(x*x + y*y);
								if (distance < MIXdistance)
								{
									MIXdistance = distance;
									MIXindex = j;
								}
							}
						}
						float dirx, diry;
						dirx = m_objects[MIXindex]->GetPositionX() - m_objects[i]->GetPositionX();
						diry = m_objects[MIXindex]->GetPositionY() - m_objects[i]->GetPositionY();
						m_objects[i]->setDirection(dirx, diry);
					}
					if (m_objects[i]->GetTeamFlag() == Red)
					{
						float distance;
						float MIXdistance = 0.0;
						int MIXindex = 3;
						if (m_objects[3] == NULL)
							break;
						for (int j = 3; j < 6; j++)
						{
							if (m_objects[j] == NULL )
								continue;
							if (m_objects[j]->GetType() != BUILDING)
								continue;
							float x = m_objects[i]->GetPositionX() - m_objects[j]->GetPositionX();
							float y = m_objects[i]->GetPositionY() - m_objects[j]->GetPositionY();
							if (j == 3)
							{
								MIXdistance = sqrt(x*x + y*y);
								MIXindex = j;
							}
							else
							{
								distance = sqrt(x*x + y*y);
								if (distance < MIXdistance)
								{
									MIXdistance = distance;
									MIXindex = j;
								}
							}
						}
						float dirx, diry;
						dirx = m_objects[MIXindex]->GetPositionX() - m_objects[i]->GetPositionX();
						diry = m_objects[MIXindex]->GetPositionY() - m_objects[i]->GetPositionY();
						m_objects[i]->setDirection(dirx, diry);
					}
				}
			}
		}
	}
}
void SceneMgr::SetAICharacter03(DWORD time)
{
	float dirX = 0.0f;
	float dirY = 0.0f;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
		{
			// NULL CHECK
			if ((m_objects[i] == NULL) || m_objects[j] == NULL) continue;
			// INDEX가 같을때 CHECK
			if (i == j) continue;
			// 같은 팀일때 CHECK
			if (m_objects[i]->GetTeamFlag() == m_objects[j]->GetTeamFlag())
				continue;
			if (CollisionCheck(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[j]->GetPositionX(), m_objects[j]->GetPositionY(), CHARACTER3_BORDER, m_objects[j]->GetSize()))
			{
				if ((m_objects[i]->GetType() == CHARACTER_3) && (m_objects[j]->GetType() == BUILDING))
				{
					((Character_T3*)m_objects[i])->SetMove(false);
					((Character_T3*)m_objects[i])->SetIndex(j);
					break;
				}
				else if ((m_objects[i]->GetType() == CHARACTER_3) && (m_objects[j]->GetType() == CHARACTER_1))
				{
					((Character_T3*)m_objects[i])->SetMove(false);
					((Character_T3*)m_objects[i])->SetIndex(j);
					break;
				}
				else if ((m_objects[i]->GetType() == CHARACTER_3) && (m_objects[j]->GetType() == CHARACTER_2))
				{
					((Character_T3*)m_objects[i])->SetMove(false);
					((Character_T3*)m_objects[i])->SetIndex(j);
					break;
				}
				else if ((m_objects[i]->GetType() == CHARACTER_3) && (m_objects[j]->GetType() == CHARACTER_3))
				{
					((Character_T3*)m_objects[i])->SetMove(false);
					((Character_T3*)m_objects[i])->SetIndex(j);
					break;
				}
			}
		}
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i]->GetType() == CHARACTER_3)
		{
			if (((Character_T3*)m_objects[i])->CreateArrow(time) && ((Character_T3*)m_objects[i])->GetMove() == false)
			{
				if (m_objects[((Character_T3*)m_objects[i])->GetIndex()] == NULL)
					break;
				dirX = m_objects[((Character_T3*)m_objects[i])->GetIndex()]->GetPositionX() - m_objects[i]->GetPositionX();
				dirY = m_objects[((Character_T3*)m_objects[i])->GetIndex()]->GetPositionY() - m_objects[i]->GetPositionY();
				for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
				{
					if (m_objects[j] != NULL)
						continue;
					m_objects[j] = new Arrow(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), ARROW, m_objects[i]->GetTeamFlag());
					m_objects[j]->setParentNode(m_objects[i]);
					m_objects[j]->setDirection(dirX, dirY);
					break;
				}
				break;
			}
		}
	}

}
void SceneMgr::UpdateObjectNum()
{
	TeamObjectNum tempRed = { 0,0,0,0 };
	TeamObjectNum tempBlue = { 0,0,0,0 };
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->GetType() == BUILDING)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
					tempRed.BUILDING_NUM++;
				else if (m_objects[i]->GetTeamFlag() == Blue)
					tempBlue.BUILDING_NUM++;
			}
			else if (m_objects[i]->GetType() == CHARACTER_1)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
					tempRed.CHARACTER1_NUM++;
				else if (m_objects[i]->GetTeamFlag() == Blue)
					tempBlue.CHARACTER1_NUM++;
			}
			else if (m_objects[i]->GetType() == CHARACTER_2)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
					tempRed.CHARACTER2_NUM++;
				else if (m_objects[i]->GetTeamFlag() == Blue)
					tempBlue.CHARACTER2_NUM++;
			}
			else if (m_objects[i]->GetType() == CHARACTER_3)
			{
				if (m_objects[i]->GetTeamFlag() == Red)
					tempRed.CHARACTER3_NUM++;
				else if (m_objects[i]->GetTeamFlag() == Blue)
					tempBlue.CHARACTER3_NUM++;
			}
		}
	}
	RedNum = tempRed;
	BlueNum = tempBlue;
}
void SceneMgr::GameEndCheck()
{
	if (m_objects[0] == NULL)
	{
		GameEnd = true;
		Win = true;
		Lose = false;
	}
	else if (m_objects[3] == NULL)
	{
		GameEnd = true;
		Win = false;
		Lose = true;
	}
	else
	{
		if (m_objects[0]->GetType() != BUILDING)
		{
			GameEnd = true;
			Win = true;
			Lose = false;
		}
		else if (m_objects[3]->GetType() != BUILDING)
		{
			GameEnd = true;
			Win = false;
			Lose = true;
		}
	}
}
//수정 안해도 되는 것들
bool SceneMgr::CollisionCheck(float x1, float y1, float x2, float y2, float size1, float size2)
{
	if (x1 - size1 / 2 > x2 + size2 / 2)
		return false;
	if (x1 + size1 / 2 < x2 - size2 / 2)
		return false;
	if (y1 + size1 / 2 < y2 - size2 / 2)
		return false;
	if (y1 - size1 / 2 > y2 + size2 / 2)
		return false;

	return true;
} 
void SceneMgr::DeleteBulletArrow()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i]->GetType() == ARROW)
		{
			if (((Arrow*)m_objects[i])->GetErase())
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
		else if (m_objects[i]->GetType() == BULLET)
		{
			if (((Bullet*)m_objects[i])->GetErase())
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}
} 
void SceneMgr::AddObject(float x, float y, Type ObjectType, Object* Parent, Team flag)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			continue;
		if (ObjectType == BUILDING)
		{
			m_objects[i] = new Building(x, y, ObjectType, flag);
			break;
		}
		else if (ObjectType == CHARACTER_1)
		{
			m_objects[i] = new Character_T1(x, y, ObjectType, flag);
			break;
		}
		else if (ObjectType == CHARACTER_2)
		{
			m_objects[i] = new Character_T2(x, y, ObjectType, flag);
			break;
		}
		else if (ObjectType == CHARACTER_3)
		{
			m_objects[i] = new Character_T3(x, y, ObjectType, flag);
			break;
		}
		else if (ObjectType == BULLET)
		{
			m_objects[i] = new Bullet(x, y, ObjectType, flag);
			m_objects[i]->setParentNode(Parent);
			break;
		}
	}
}
