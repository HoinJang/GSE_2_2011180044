#pragma once
class Scene
{
public:
	Scene()
	{
	}
	virtual ~Scene()
	{
	}
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual bool KeyBoard() = 0;
};
