#include "GridUi.h"
#include "../Framework/Framework.h"
#include "../GameObject/GridRectTile.h"
#include "../Scene/SceneMgr.h"
#include "../Ui/MapEditorUiMgr.h"

GridUi::GridUi()
{
}

GridUi::~GridUi()
{
}

void GridUi::Init()
{
	Object::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();	

	int row = windowSize.x / 32;
	int column = windowSize.y / 32;
	for (int i = 0; i < column; ++i)
	{
		vector<GridRectTile*>* tiles = new vector<GridRectTile*>;
		for (int j = 0; j < row; ++j)
		{
			GridRectTile* tile = new GridRectTile();
			tile->Init();
			tile->SetSize({ 24.f, 24.f });
			tile->SetPos({ windowSize.x * 0.02f + 28.f * j, windowSize.y * 0.1f + 28.f * i });
			tile->ClickOn = bind(&RectTile::SetTexture, tile, ((MapEditorUiMgr*)(SCENE_MGR->GetScene(Scenes::MapEditor)->GetUiMgr()))->GetTexture());
			tiles->push_back(tile);
		}
		map.push_back(tiles);
	}
}

void GridUi::Update(float dt)
{
	Object::Update(dt);
	for (auto tiles : map)
	{
		for (auto tile : *tiles)
		{
			tile->Update(dt);
		}
	}
}

void GridUi::Draw(RenderWindow& window)
{
	Object::Draw(window);
	for (auto tiles : map)
	{
		for (auto tile : *tiles)
		{
			tile->Draw(window);
		}
	}
}
