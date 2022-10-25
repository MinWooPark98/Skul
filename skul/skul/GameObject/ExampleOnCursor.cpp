#include "ExampleOnCursor.h"
#include "../Framework/InputMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"

ExampleOnCursor::ExampleOnCursor()
{
}

ExampleOnCursor::~ExampleOnCursor()
{
}

void ExampleOnCursor::Update(float dt)
{
	SpriteObj::Update(dt);
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	SetPos(mapEditorScene->GetObjMousePos());
	string currObjName = (mapEditorScene->GetObjName());
	if (recentName != currObjName)
	{
		recentName = currObjName;
		if (currObjName.empty() || mapEditorScene->GetMode() == MapEditorScene::Modes::TileCollider)
		{
			SetColor({ 255, 255, 255, 0 });
			return;
		}
		FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
		filePath->SetObjType((FilePathTable::ObjTypes)((int)mapEditorScene->GetMode()));
		SetTexture(*RESOURCE_MGR->GetTexture(filePath->Get(recentName)));
		SetOrigin(Origins::MC);
		SetColor({ 255, 255, 255, 204 });
	}
}

void ExampleOnCursor::Draw(RenderWindow& window)
{
	if (InputMgr::GetMousePos().x >= FRAMEWORK->GetWindowSize().x * 0.9f ||
		((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->GetPause())
	{
		return;
	}
	SpriteObj::Draw(window);
}
