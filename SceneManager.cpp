#include "SceneManager.h"
SceneManager::SceneManager()
{
	pScene = nullptr;
	pSceneList.clear();
}
SceneManager::~SceneManager()
{
	for (int i = 0; i < pSceneList.size(); ++i)
		SAFE_DELETE(pSceneList[i].p);
	pSceneList.clear();
}
void SceneManager::Entry(int num, Scene* p)
{
	pSceneList.emplace_back(num, p);
}
void SceneManager::Trans(int num)
{
	if (pScene != nullptr)
		pScene->Destroy();
	auto find = find_if(pSceneList.begin(), pSceneList.end(), [&](const SceneData& p)
	{
		return p.num == num;
	});
	pScene = find->p;
	pScene->Init();
}