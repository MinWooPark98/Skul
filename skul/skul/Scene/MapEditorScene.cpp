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
	Vector2i windowSize = FRAMEWORK->GetWindowSize();
	int row = windowSize.x / 32;
	int column = windowSize.y / 32;
	for (int i = 0; i < column; ++i)
	{
		vector<Tile*>* tiles = new vector<Tile*>;
		for (int j = 0; j < row; ++j)
		{
			Tile* tile = new Tile();
			tile->SetSize({ 24.f, 24.f });
			tile->SetPos({ windowSize.x * 0.02f + 28.f * j, windowSize.y * 0.1f + 28.f * i });
			tiles->push_back(tile);
			objList.push_back(tile);
		}
		map.push_back(tiles);
	}

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
