#pragma once
#include "Scene.h"
#include "myInclude.h"
#include "myDefine.h"
#include "stdafx.h"

using namespace std;
struct SceneData
{
	int num;
	Scene* p;

	SceneData(int num, Scene* p) : num(num), p(p)
	{

	}
};
class SceneManager
{
private:
	vector<SceneData> pSceneList;
	Scene*	pScene; // ÇöÀç¾À
public:
	SceneManager();
	~SceneManager();
public:
	void Entry(int num, Scene* p);
	void Trans(int num);
#pragma region get,set
	Scene* getScene() const { return pScene; }
#pragma endregion

};