#include "ObjExampleUi.h"
#include "../GameObject/ExRectTile.h"
#include "../Framework/ResourceMgr.h"
#include "ListMoverUi.h"
#include <fstream>
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"

ObjExampleUi::ObjExampleUi()
	:currTile(0), clickedTile(nullptr), listMover(nullptr)
{
}

ObjExampleUi::~ObjExampleUi()
{
}

void ObjExampleUi::Init()
{
	Object::Init();
	FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
	ifstream ifs(tileNames);
	string tileName;
	Vector2f frameSize = { 88.f, 184.f };
	Vector2f tileSize;
	while (true)
	{
		ExRectTile* tile = new ExRectTile();
		tile->Init();
		Texture* tex;
		if (getline(ifs, tileName))
			tex = (RESOURCE_MGR->GetTexture(filePath->Get(tileName)));
		else
		{
			delete tile;
			break;
		}
		Vector2f texSize = Vector2f((*tex).getSize());
		if (texSize.x / frameSize.x > texSize.y / frameSize.y)
			tileSize = { frameSize.x, texSize.y / (texSize.x / frameSize.x) };
		else
			tileSize = { texSize.x / (texSize.y / frameSize.y), frameSize.y };
		tile->SetSize(tileSize);
		tile->SetTexture(tex);
		tile->SetName(tileName);
		tiles.push_back(tile);
	}
	ifs.close();

	listMover = new ListMoverUi();
	listMover->Init();
	listMover->SetSize(12);
	listMover->SetDistance(44.f);
	listMover->SetPos({ 12.f, 200.f });
	listMover->ShowPrev = bind(&ObjExampleUi::ShowPrevTiles, this);
	listMover->ShowNext = bind(&ObjExampleUi::ShowNextTiles, this);
}

void ObjExampleUi::Release()
{
	for (auto tile : tiles)
	{
		delete tile;
		tile = nullptr;
	}
	if (listMover != nullptr)
		delete listMover;
	listMover = nullptr;
}

void ObjExampleUi::Reset()
{
	currTile = 0;
	if (clickedTile != nullptr)
	{
		clickedTile->SetClicked(false);
		clickedTile->ClickedOff();
	}
	clickedTile = nullptr;
	((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->ClearObjName();
	SetActive(false);
}

void ObjExampleUi::Update(float dt)
{
	tiles[currTile]->Update(dt);
	if (tiles[currTile]->GetClicked() && tiles[currTile] != clickedTile)
	{
		if (clickedTile != nullptr)
		{
			clickedTile->SetClicked(false);
			clickedTile->ClickedOff();
		}
		clickedTile = tiles[currTile];
		((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->SetObjName(clickedTile->GetName());
	}
	listMover->Update(dt);
}

void ObjExampleUi::Draw(RenderWindow& window)
{
	tiles[currTile]->Draw(window);
	listMover->Draw(window);
}

void ObjExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tile : tiles)
	{
		tile->Translate(pos);
	}
	listMover->Translate(pos);
}

void ObjExampleUi::ShowPrevTiles()
{
	if (currTile > 0)
		currTile -= 1;
}

void ObjExampleUi::ShowNextTiles()
{
	if (currTile < tiles.size() - 1)
		currTile += 1;
}
