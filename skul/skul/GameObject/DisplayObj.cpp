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
		InputMgr::GetMousePos().x >= FRAMEWORK->GetWindowSize().x * 0.9f)
	{
		return;
	}
	if (InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		string objName = mapEditorScene->GetObjName();
		if (objName.empty())
			return;
		SpriteObj* obj = displays.Get();
		FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
		filePath->SetObjType((FilePathTable::ObjTypes)((int)mapEditorScene->GetMode()));
		obj->SetTexture(*RESOURCE_MGR->GetTexture(filePath->Get(objName)));
		obj->SetOrigin(Origins::BC);
		obj->SetPos({ mousePos.x, mousePos.y + obj->GetGlobalBounds().height * 0.5f });
	}
	list<SpriteObj*> useList = displays.GetUseList();
	for (auto obj : useList)
	{
		if (obj->GetGlobalBounds().contains(mousePos) && InputMgr::GetMouseButtonDown(Mouse::Right))
			displays.Return(obj);
	}
}

void DisplayObj::Draw(RenderWindow& window)
{
	list<SpriteObj*> useList = displays.GetUseList();
	for (auto obj : useList)
	{
		obj->Draw(window);
	}
}
