#include "MapEditorScene.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/Tile.h"
#include "../Ui/MapEditorUiMgr.h"

MapEditorScene::MapEditorScene()
	:Scene(Scenes::MapEditor)
{
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::Init()
{
	uiMgr = new MapEditorUiMgr();
	objList.push_back(uiMgr);

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void MapEditorScene::Release()
{
}

void MapEditorScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}

void MapEditorScene::Update(float dt)
{
	Scene::Update(dt);
}

void MapEditorScene::Enter()
{
	Scene::Enter();
}

void MapEditorScene::Exit()
{
}
