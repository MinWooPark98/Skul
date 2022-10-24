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
		switch (mapEditorScene->GetMode())
		{
		case MapEditorScene::Modes::BackGround:
			layout[(int)MapEditorScene::Layer::BackGround]->push_back(obj);
			break;
		case MapEditorScene::Modes::BackObject:
			layout[(int)MapEditorScene::Layer::BackObject]->push_back(obj);
			break;
		case MapEditorScene::Modes::Player:
			if (!(layout[(int)MapEditorScene::Layer::Player]->empty()))
			{
				SpriteObj* player = (SpriteObj*)layout[(int)MapEditorScene::Layer::Player]->front();
				player->SetPos({ mousePos.x, mousePos.y + player->GetGlobalBounds().height * 0.5f });// player놈 uselist에서 return하고 걍 새로 넣는 걸로
				delete obj;
				return;
			}
			layout[(int)MapEditorScene::Layer::Player]->push_back(obj);
			break;
		case MapEditorScene::Modes::Tile:
			layout[(int)MapEditorScene::Layer::Tile]->push_back(obj);
			break;
		case MapEditorScene::Modes::TileCollider:
			layout[(int)MapEditorScene::Layer::Collider]->push_back(obj);
			break;
		default:
			layout[(int)MapEditorScene::Layer::ActivateObject]->push_back(obj);
			break;
		}
		FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
		filePath->SetObjType((FilePathTable::ObjTypes)((int)mapEditorScene->GetMode()));
		obj->SetTexture(*RESOURCE_MGR->GetTexture(filePath->Get(objName)));
		obj->SetOrigin(Origins::BC);
		obj->SetPos({ mousePos.x, mousePos.y + obj->GetGlobalBounds().height * 0.5f });
	}
}/*

void DisplayObj::Draw(RenderWindow& window)
{
	list<SpriteObj*> useList = displays.GetUseList();
	for (auto obj : useList)
	{
		obj->Draw(window);
	}
}*/
