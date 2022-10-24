#include "MapEditorDataMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/Utils.h"
#include "Grid.h"
#include "GridRectTile.h"
#include "DisplayObj.h"
#include "DisplayCollider.h"
#include "SpriteObj.h"
#include "DragRectTile.h"
#include <fstream>

MapEditorDataMgr::MapEditorDataMgr()
{
}

MapEditorDataMgr::~MapEditorDataMgr()
{
	ClearData();
}

void MapEditorDataMgr::SaveData()
{
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	auto& grid = ((Grid*)mapEditorScene->FindGameObj("grid"))->Get();
	for (auto tiles : grid)
	{
		for (auto tile : *tiles)
		{
			mapData.push_back(MapData((int)MapEditorScene::Modes::Tile, tile->GetName(), tile->GetPos(), tile->GetSize(), (int)Origins::TL, (int)MapEditorScene::Layer::Tile));
		}
	}
	auto& objSeperated = ((DisplayObj*)mapEditorScene->FindGameObj("displayObj"))->Get();
	for (int i = 0; i < objSeperated.size(); ++i)
	{
		for (auto obj : *objSeperated[i])
		{
			int layer;
			switch (MapEditorScene::Modes(i))
			{
			case MapEditorScene::Modes::BackGround:
				layer = (int)MapEditorScene::Layer::BackGround;
				break;
			case MapEditorScene::Modes::BackObject:
				layer = (int)MapEditorScene::Layer::BackObject;
				break;
			case MapEditorScene::Modes::Player:
				layer = (int)MapEditorScene::Layer::Player;
				break;
			case MapEditorScene::Modes::Enemies:
			case MapEditorScene::Modes::NPC:
			case MapEditorScene::Modes::Reward:
				layer = (int)MapEditorScene::Layer::ActivateObject;
				break;
			}
			mapData.push_back(MapData(i, obj->GetName(), obj->GetPos(), obj->GetSize(), (int)Origins::BC, layer));
		}
	}
	auto displayCollider = ((DisplayCollider*)mapEditorScene->FindGameObj("displayCollider"))->Get();
	for (auto collider : displayCollider)
	{
		mapData.push_back(MapData((int)MapEditorScene::Modes::TileCollider, collider->GetName(), collider->GetPos(), collider->GetSize(), (int)Origins::TL, (int)MapEditorScene::Layer::Collider));
	}

	json j_list(mapData);
	ofstream ofs("test.json");
	ofs << j_list;
}

void MapEditorDataMgr::ClearData()
{
	mapData.clear();
}
