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
			MapData* data = new MapData((int)MapEditorScene::Modes::Tile, tile->GetName(), tile->GetPos(), tile->GetSize(), (int)Origins::TL, (int)MapEditorScene::Layer::Tile);
			mapData.push_back(data);
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
			MapData* data = new MapData(i, obj->GetName(), obj->GetPos(), obj->GetSize(), (int)Origins::BC, layer);
			mapData.push_back(data);
		}
	}
	auto displayCollider = ((DisplayCollider*)mapEditorScene->FindGameObj("displayCollider"))->Get();
	for (auto collider : displayCollider)
	{
		MapData* data = new MapData((int)MapEditorScene::Modes::TileCollider, collider->GetName(), collider->GetPos(), collider->GetSize(), (int)Origins::TL, (int)MapEditorScene::Layer::Collider);
		mapData.push_back(data);
	}

	for (auto data : mapData)
	{
		cout << data->objType << " " << data->objName << " " << data->xPos << ", " << data->yPos << " " << data->width << " " << data->height << " " << data->origin << " " << data->layer << endl;
	}
}

void MapEditorDataMgr::ClearData()
{
	for (auto data : mapData)
	{
		delete data;
		data = nullptr;
	}
	mapData.clear();
}
