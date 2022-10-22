#include "TileExampleUi.h"
#include "../GameObject/ExRectTile.h"
#include "../GameObject/TextObj.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"

TileExampleUi::TileExampleUi()
	:currList(0), clickedTile(nullptr)
{
}

TileExampleUi::~TileExampleUi()
{
}

void TileExampleUi::Init()
{
	Object::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();
	for (int i = 0; i < 3; ++i)
	{
		list<ExRectTile*>* tileList = new list<ExRectTile*>;
		for (int j = 0; j < 8; ++j)
		{
			ExRectTile* tile = new ExRectTile();
			tile->Init();
			tile->SetSize({ 40.f, 40.f });
			tile->SetPos({ 48.f * (j % 2), 48.f * (j / 2) });
			if (j < 4)
				tile->SetTexture(RESOURCE_MGR->GetTexture("graphics/player3.png"));
			else
				tile->SetTexture(nullptr);
			tileList->push_back(tile);
		}
		tiles.push_back(tileList);
	}
}

void TileExampleUi::Release()
{
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
}

void TileExampleUi::Draw(RenderWindow& window)
{
	for (auto tile : *tiles[currList])
	{
		tile->Draw(window);
	}
}

void TileExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tileList : tiles)
	{
		for(auto tile : *tileList)
			tile->Translate(pos);
	}
}
