#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <map>
#include "../3rd/Singleton.h"

class PlayerDataStorage;

using namespace sf;
using namespace std;

class SceneMgr : public Singleton<SceneMgr>
{
private:
	map<Scenes, Scene*> sceneMap;
	Scenes currScene;

	PlayerDataStorage* playerData;

public:
	bool Init();

	Scene* GetScene(Scenes scene);
	void ChangeScene(Scenes scene);
	Scene* GetCurrentScene();

	void Update(float dt);
	void Draw(RenderWindow& window);

	PlayerDataStorage* GetPlayerDataStorage() { return playerData; }
};

#define SCENE_MGR (SceneMgr::GetInstance())