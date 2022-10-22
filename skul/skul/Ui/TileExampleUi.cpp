#include "TileExampleUi.h"
#include "../GameObject/ExRectTile.h"
#include "../Framework/ResourceMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"
#include "ListMoverUi.h"
#include <fstream>
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"

TileExampleUi::TileExampleUi()
	:currList(0), clickedTile(nullptr), listMover(nullptr)
{
}

TileExampleUi::~TileExampleUi()
{
}

void TileExampleUi::Init()
{
	Object::Init();
	FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
	ifstream ifs(tileNames);
	string tileName;
	bool tileRemain = true;
	while (tileRemain)
	{
		list<ExRectTile*>* tileList = new list<ExRectTile*>;
		for (int i = 0; i < 8; ++i)
		{
			ExRectTile* tile = new ExRectTile();
			tile->Init();
			tile->SetSize({ 40.f, 40.f });
			tile->SetPos({ 48.f * (i % 2), 48.f * (i / 2) });
			
			if (tiles.size() == 0 && tileList->size() == 0)
				tile->SetTexture(nullptr);
			else if (getline(ifs, tileName))
				tile->SetTexture(RESOURCE_MGR->GetTexture(filePath->Get(tileName)));
			else
			{
				delete tile;
				tileRemain = false;
				break;
			}
			tileList->push_back(tile);
		}
		tiles.push_back(tileList);
	}
	ifs.close();

	listMover = new ListMoverUi();
	listMover->Init();
	listMover->SetSize(12);
	listMover->SetDistance(44.f);
	listMover->SetPos({ 12.f, 200.f });
	listMover->ShowPrev = bind(&TileExampleUi::ShowPrevTiles, this);
	listMover->ShowNext = bind(&TileExampleUi::ShowNextTiles, this);
}

void TileExampleUi::Release()
{
	for (auto tileList : tiles)
	{
		for (auto tile : *tileList)
		{
			delete tile;
			tile = nullptr;
		}
	}
	if(listMover != nullptr)
		delete listMover;
	listMover = nullptr;
}

void TileExampleUi::Reset()
{
	enabled = false;
}

void TileExampleUi::Update(float dt)
{
	for (auto tile : *tiles[currList])
	{
		tile->Update(dt);
		if (tile->GetClicked() && tile != clickedTile)
		{
			if (clickedTile != nullptr)
			{
				clickedTile->SetClicked(false);
				clickedTile->ClickedOff();
			}
			clickedTile = tile;
			((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->SetTexture(clickedTile->GetTexture());
		}
	}
	listMover->Update(dt);
}

void TileExampleUi::Draw(RenderWindow& window)
{
	for (auto tile : *tiles[currList])
	{
		tile->Draw(window);
	}
	listMover->Draw(window);
}

void TileExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tileList : tiles)
	{
		for(auto tile : *tileList)
			tile->Translate(pos);
	}
	listMover->Translate(pos);
}

void TileExampleUi::ShowPrevTiles()
{
	if (currList > 0)
		currList -= 1;
}

void TileExampleUi::ShowNextTiles()
{
	if (currList < tiles.size() - 1)
		currList += 1;
}
