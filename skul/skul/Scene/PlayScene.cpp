#include "PlayScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Skul/DefaultSkul.h"
#include "../Framework/Framework.h"
#include "../GameObject/Collider.h"
#include "../GameObject/Enemy/SwordsMan.h"
#include "../GameObject/MapEditorDataMgr.h"
#include <fstream>
#include "../GameObject/RectTile.h"
#include "../GameObject/PlaySceneGrid.h"
#include "MapEditorScene.h"
#include "../Framework/InputMgr.h"
#include "../Datatable/FilePathTable.h"
#include "../DataTable/DataTableMGR.h"
#include "../Framework/ResourceMgr.h"

PlayScene::PlayScene()
	:Scene(Scenes::Play)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	for (int i = 0; i < (int)Layer::Count; ++i)
	{
		list<Object*>* objects = new list<Object*>;
		layOut.push_back(objects);
	}

	vector<list<MapEditorDataMgr::MapData>> mapData;
	for (int i = 0; i < 3; ++i)
	{
		mapData.push_back(list<MapEditorDataMgr::MapData>());
	}
	ifstream ifs("test.json");
	if (ifs.fail())
		return;
	json jsonData;
	ifs >> jsonData;
	ifs.close();
	int vecIdx = 0;
	for (auto vecIt = jsonData.begin(); vecIt != jsonData.end(); ++vecIt)
	{
		for (auto listIt = (*vecIt).begin(); listIt != (*vecIt).end(); ++listIt)
		{
			MapEditorDataMgr::MapData data;
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
	PlaySceneGrid* grid = new PlaySceneGrid();
	grid->Load(mapData[0]);
	layOut[(int)Layer::Tile]->push_back(grid);
	objList.push_back(grid);
	
	for (auto& data : mapData[1])
	{
		Object* obj = nullptr;
		switch ((MapEditorScene::Modes)data.objType)
		{
		case MapEditorScene::Modes::BackGround:
		case MapEditorScene::Modes::BackObject:
			{
				obj = new SpriteObj();
				FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
				filePath->SetObjType((FilePathTable::ObjTypes)data.objType);
				((SpriteObj*)obj)->SetTexture(*RESOURCE_MGR->GetTexture(filePath->Get(data.objName)));
				((SpriteObj*)obj)->SetOrigin((Origins)data.origin);
			}
			break;
		case MapEditorScene::Modes::Reward:
			break;
		case MapEditorScene::Modes::NPC:
			break;
		case MapEditorScene::Modes::Enemies:
			{
				if (data.objName == "enemy_0")
					obj = new SwordsMan();
			}
			break;
		case MapEditorScene::Modes::Player:
			{
				obj = new Player();

				Skul* skul = new DefaultSkul();
				skul->Init();
				((Player*)obj)->SetSkul(skul);
			}
			break;
		default:
			break;
		}
		if (obj != nullptr)
		{
			obj->Init();
			obj->SetPos({ data.xPos, data.yPos });
			layOut[(int)data.layer]->push_back(obj);
			objList.push_back(obj);
		}
	}

	for (auto& data : mapData[2])
	{
		Collider* collider = new Collider();
		collider->Init();
		if (data.objName == "TopSide")
			collider->SetType(Collider::Type::TopSide);
		else
			collider->SetType(Collider::Type::AllSide);
		collider->SetPos({ data.xPos, data.yPos });
		collider->SetHitBox({ 0.f, 0.f, data.width, data.height });
		layOut[data.layer]->push_back(collider);
		objList.push_back(collider);
	}
}

void PlayScene::Release()
{
	Scene::Release();
}

void PlayScene::Reset()
{
	Scene::Reset();
}

void PlayScene::Update(float dt)
{
	if (dt >= 0.05f)
		return;
	Scene::Update(dt);
	worldView.setCenter(FindGameObj("player")->GetPos());

	if (InputMgr::GetKeyDown(Keyboard::F1))
	{
		for (auto obj : objList)
		{
			obj->SwitchDevMode();
		}
	}
}

void PlayScene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	for (auto layers : layOut)
	{
		for (auto obj : *layers)
		{
			if (obj->GetActive())
				obj->Draw(window);
		}
	}
	window.setView(uiView);
	//uiMgr->Draw(window);
}

void PlayScene::Enter()
{
	Scene::Enter();

	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x * 0.5f, size.y * 0.5f);
	worldView.setCenter(size.x * 0.5f, size.y * 0.75f);

	uiView.setSize(size.x, size.y);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void PlayScene::Exit()
{
}
