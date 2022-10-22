#include "Grid.h"
#include "../Framework/Framework.h"
#include "../GameObject/GridRectTile.h"
#include "../Scene/SceneMgr.h"
#include "../Ui/MapEditorUiMgr.h"

Grid::Grid()
{
}

Grid::~Grid()
{
}

void Grid::Init()
{
	Object::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();	

	int row = windowSize.x / 32 * 2;
	int column = windowSize.y / 32 * 2;
	for (int i = 0; i < column; ++i)
	{
		vector<GridRectTile*>* tiles = new vector<GridRectTile*>;
		for (int j = 0; j < row; ++j)
		{
			GridRectTile* tile = new GridRectTile();
			tile->Init();
			tile->SetSize({ 28.f, 28.f });
			tile->SetPos({ 2.f + 32.f * j, 2.f + 32.f * i });
			tiles->push_back(tile);
		}
		map.push_back(tiles);
	}
}

void Grid::Update(float dt)
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

void Grid::Draw(RenderWindow& window)
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
