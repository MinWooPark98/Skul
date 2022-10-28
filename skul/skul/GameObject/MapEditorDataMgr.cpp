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

void MapEditorDataMgr::Init()
{
	for (int i = 0; i < 3; ++i)
	{
		mapData.push_back(list<MapData>());
	}
}

void MapEditorDataMgr::Release()
{
}

void MapEditorDataMgr::Reset()
{
	for (int i = 0; i < 3; ++i)
	{
		mapData[i].clear();
	}
}

bool MapEditorDataMgr::SaveData(const string& filePath)
{
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	Reset();
	auto& grid = ((Grid*)mapEditorScene->FindGameObj("grid"))->Get();
	for (auto tiles : grid)
	{
		for (auto tile : *tiles)
		{
			mapData[0].push_back(MapData((int)MapEditorScene::Modes::Tile, tile->GetName(), tile->GetPos(), tile->GetSize(), (int)Origins::TL, (int)MapEditorScene::Layer::Tile));
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
				layer = (int)MapEditorScene::Layer::Enemy;
				break;
			case MapEditorScene::Modes::NPC:
				layer = (int)MapEditorScene::Layer::NPC;
				break;
			case MapEditorScene::Modes::Reward:
				layer = (int)MapEditorScene::Layer::Reward;
				break;
			}
			mapData[1].push_back(MapData(i, obj->GetName(), obj->GetPos(), obj->GetSize(), (int)Origins::BC, layer));
		}
	}
	auto displayCollider = ((DisplayCollider*)mapEditorScene->FindGameObj("displayCollider"))->Get();
	for (auto collider : displayCollider)
	{
		mapData[2].push_back(MapData((int)MapEditorScene::Modes::TileCollider, collider->GetName(), collider->GetPos(), collider->GetSize(), (int)Origins::TL, (int)MapEditorScene::Layer::Collider));
	}

	json mapObjData(mapData);
	ofstream ofs(filePath + ".json");
	if (ofs.fail())
		return false;
	ofs << mapObjData;
	ofs.close();
	return true;
}

bool MapEditorDataMgr::LoadData(const string& filePath)
{
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	Reset();
	ifstream ifs(filePath + ".json");
	if (ifs.fail())
		return false;
	json jsonData;
	ifs >> jsonData;
	ifs.close();
	mapEditorScene->Reset();
	int vecIdx = 0;
	for (auto vecIt = jsonData.begin(); vecIt != jsonData.end(); ++vecIt)
	{
		for (auto listIt = (*vecIt).begin(); listIt != (*vecIt).end(); ++listIt)
		{
			MapData data;
			data.objType = (*listIt)["objType"];
			data.objName = (*listIt)["objName"];
			data.xPos = (*listIt)["xPos"];
			data.yPos = (*listIt)["yPos"];
			data.width = (*listIt)["width"];
			data.height = (*listIt)["height"];
			data.origin = (*listIt)["origin"];
			data.layer = (*listIt)["layer"];
			mapData[vecIdx].push_back(data);
		}
		++vecIdx;
	}
	auto grid = ((Grid*)mapEditorScene->FindGameObj("grid"));
	auto displayObj = (DisplayObj*)mapEditorScene->FindGameObj("displayObj");
	auto displayCollider = (DisplayCollider*)mapEditorScene->FindGameObj("displayCollider");
	for (int i = 0; i < 3; ++i)
	{
		switch (i)
		{
		case 0:
			grid->Load(mapData[i]);
			break;
		case 1:
			for (auto& data : mapData[i])
			{
				displayObj->Load(data);
			}
			break;
		case 2:
			for (auto& data : mapData[i])
			{
				displayCollider->Load(data);
			}
			break;
		}
	}
	return true;
}

void MapEditorDataMgr::ClearData()
{
	mapData.clear();
}
