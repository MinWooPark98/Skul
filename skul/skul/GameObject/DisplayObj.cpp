#include "DisplayObj.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../Framework/InputMgr.h"
#include "SpriteObj.h"
#include "../Framework/Framework.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"
#include "../Framework/ResourceMgr.h"

DisplayObj::DisplayObj()
{
}

DisplayObj::~DisplayObj()
{
}

void DisplayObj::Init()
{
	Object::Init();
	displays.Init();
	for (int i = 0; i < 7; ++i)
	{
		list<SpriteObj*>* objs = new list<SpriteObj*>;
		objSeperated.push_back(objs);
	}
}

void DisplayObj::Release()
{
	Object::Release();
	displays.Release();
}

void DisplayObj::Reset()
{
	Object::Reset();
	displays.Reset();
	for (auto objs : objSeperated)
	{
		objs->clear();
	}
}

void DisplayObj::Update(float dt)
{
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	Vector2f mousePos = mapEditorScene->GetObjMousePos();
	if (mapEditorScene->GetMode() == MapEditorScene::Modes::None ||
		mapEditorScene->GetMode() == MapEditorScene::Modes::Tile ||
		mapEditorScene->GetMode() == MapEditorScene::Modes::TileCollider ||
		InputMgr::GetMousePos().x >= FRAMEWORK->GetWindowSize().x * 0.9f)
	{
		return;
	}

	auto& layout = mapEditorScene->GetLayout();

	list<SpriteObj*> useList = displays.GetUseList();
	if (InputMgr::GetKeyDown(Keyboard::BackSpace) && useList.size() > 0)
	{
		SpriteObj* objToErase = useList.back();
		for (auto objs : objSeperated)
		{
			objs->remove(objToErase);
		}
		for (auto layers : layout)
		{
			layers->remove(objToErase);
		}
		displays.Return(objToErase);
	}

	if (InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		string objName = mapEditorScene->GetObjName();
		if (objName.empty())
			return;
		SpriteObj* obj = displays.Get();
		obj->SetName(objName);
		FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
		filePath->SetObjType((FilePathTable::ObjTypes)((int)mapEditorScene->GetMode()));
		obj->SetTexture(*RESOURCE_MGR->GetTexture(filePath->Get(objName)));
		obj->SetOrigin(Origins::BC);
		obj->SetPos({ mousePos.x, mousePos.y + obj->GetGlobalBounds().height * 0.5f });
		switch (mapEditorScene->GetMode())
		{
		case MapEditorScene::Modes::BackGround:
			layout[(int)MapEditorScene::Layer::BackGround]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::BackGround]->push_back(obj);
			break;
		case MapEditorScene::Modes::BackObject:
			layout[(int)MapEditorScene::Layer::BackObject]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::BackObject]->push_back(obj);
			break;
		case MapEditorScene::Modes::Player:
			if (!(layout[(int)MapEditorScene::Layer::Player]->empty()))
			{
				SpriteObj* player = (SpriteObj*)layout[(int)MapEditorScene::Layer::Player]->front();
				layout[(int)MapEditorScene::Layer::Player]->remove(player);
				objSeperated[(int)MapEditorScene::Modes::Player]->remove(player);
				displays.Return(player);
			}
			layout[(int)MapEditorScene::Layer::Player]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::Player]->push_back(obj);
			break;
		case MapEditorScene::Modes::Enemies:
			layout[(int)MapEditorScene::Layer::Enemy]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::Enemies]->push_back(obj);
			break;
		case MapEditorScene::Modes::NPC:
			layout[(int)MapEditorScene::Layer::NPC]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::NPC]->push_back(obj);
			break;
		case MapEditorScene::Modes::Reward:
			layout[(int)MapEditorScene::Layer::Reward]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::Reward]->push_back(obj);
			break;
		case MapEditorScene::Modes::Gate:
			layout[(int)MapEditorScene::Layer::Gate]->push_back(obj);
			objSeperated[(int)MapEditorScene::Modes::Gate]->push_back(obj);
			break;
		}
	}
}

void DisplayObj::Load(const MapEditorDataMgr::MapData& data)
{
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	auto& layout = mapEditorScene->GetLayout();
	SpriteObj* obj = displays.Get();
	obj->SetName(data.objName);
	FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
	filePath->SetObjType((FilePathTable::ObjTypes)data.objType);
	obj->SetTexture(*RESOURCE_MGR->GetTexture(filePath->Get(data.objName)));
	obj->SetOrigin((Origins)data.origin);
	obj->SetPos({ data.xPos, data.yPos });
	layout[(int)data.layer]->push_back(obj);
	objSeperated[(int)data.objType]->push_back(obj);
}
