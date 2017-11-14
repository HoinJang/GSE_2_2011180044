#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	m_renderer = NULL;

	//b_texture = m_renderer->CreatePngTexture("./Resources/Building.png");
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
}
void SceneMgr::Init()
{
	m_renderer = new Renderer(500, 500);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	AddObject(0, 0, BUILDING, NULL);

}
void SceneMgr::Destory() 
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			delete m_objects[i];
		}
	}
	delete m_renderer;
}
void SceneMgr::Render()
{

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			/*if (m_objects[i]->GetType() == BUILDING)
			{
				m_renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0.0, m_objects[i]->GetSize(), m_objects[i]->GetColorRed(), m_objects[i]->GetColorGreen(), m_objects[i]->GetColorBlue(), 0.0, b_texture);
			}
			else*/
			{
				m_objects[i]->Render(m_renderer);
			}
		}
	}
}
void SceneMgr::Update(DWORD time)
{
	CreateBulletArrow(time);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	}
	CollisionObjectCheck();
	LifeAndLifeTimeCheck();
	DeleteBulletArrow();
}
void SceneMgr::MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			AddObject((float)(x - 250), (float)(250 - y), CHARACTER, NULL);
		}
	}
}
bool SceneMgr::CollisionCheck(float x1, float y1, float x2, float y2,  float size1 , float size2)
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
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT ; j++)
		{
			if ((m_objects[i] == NULL) || m_objects[j] == NULL) continue;
			if (i == j) continue;
			if (CollisionCheck(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), m_objects[j]->GetPositionX(), m_objects[j]->GetPositionY(), m_objects[i]->GetSize(), m_objects[j]->GetSize()))
			{
				if ((m_objects[i]->GetType() == BUILDING) && ((m_objects[j]->GetType() == CHARACTER )||(m_objects[j]->GetType() == ARROW)))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					m_objects[j]->Collision_Life(m_objects[i]->GetLife());
				}
				else if ((m_objects[i]->GetType() == CHARACTER) && (m_objects[j]->GetType() == BULLET))
				{
					m_objects[i]->Collision_Life(m_objects[j]->GetLife());
					delete m_objects[j];
					m_objects[j] = NULL;
				}
				else if ((m_objects[i]->GetType() == CHARACTER) && (m_objects[j]->GetType() == ARROW))
				{
					if (m_objects[j]->GetParentNode() != m_objects[i])
					{
						m_objects[i]->Collision_Life(m_objects[j]->GetLife());
						m_objects[j]->Collision_Life(m_objects[i]->GetLife());
					}
				}
			}
		}
	}
}
void SceneMgr::CreateBulletArrow(DWORD time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
			continue;
		if (m_objects[i]->GetType() == BUILDING)
		{
			if (((Building*)m_objects[i])->CreateBullet(time))
			{
				AddObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), BULLET, m_objects[i]);
			}
		}
		else if (m_objects[i]->GetType() == CHARACTER)
		{
			if (((Character*)m_objects[i])->CreateArrow(time))
			{
				AddObject(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), ARROW, m_objects[i]);
			}
		}
	}
}
void SceneMgr::AddObject(float x, float y, Type ObjectType, Object* Parent)
{

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			continue;
		if (ObjectType == BUILDING)
		{
			m_objects[i] = new Building(x, y, ObjectType);
			break;
		}
		else if (ObjectType == CHARACTER)
		{
			m_objects[i] = new Character(x, y, ObjectType);
			break;
		}
		else if (ObjectType == BULLET)
		{
			m_objects[i] = new Bullet(x, y, ObjectType);
			m_objects[i]->setParentNode(Parent);
			break;
		}
		else if (ObjectType == ARROW)
		{
			m_objects[i] = new Arrow(x, y, ObjectType);
			m_objects[i]->setParentNode(Parent);
			break;
		}
	}
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
