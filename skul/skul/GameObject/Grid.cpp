#include "Grid.h"
#include "../Framework/Framework.h"
#include "../GameObject/GridRectTile.h"
#include "../Scene/SceneMgr.h"
#include "../Ui/MapEditorUiMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"
#include "../Framework/ResourceMgr.h"

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

	int row = windowSize.x / 16;
	int column = windowSize.y / 16;
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
		grid.push_back(tiles);
	}
}

void Grid::Release()
{
	for (auto tiles : grid)
	{
		for (auto tile : *tiles)
		{
			delete tile;
		}
		tiles->clear();
	}
	grid.clear();
}

void Grid::Reset()
{
	for (auto tiles : grid)
	{
		for (auto tile : *tiles)
		{
			tile->Reset();
		}
	}
}

void Grid::Update(float dt)
{
	Object::Update(dt);
	for (auto tiles : grid)
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
	for (auto tiles : grid)
	{
		for (auto tile : *tiles)
		{
			tile->Draw(window);
		}
	}
}

void Grid::Load(const list<MapEditorDataMgr::MapData>& data)
{
	Release();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();
	int row = windowSize.x / 16;
	int column = windowSize.y / 16;
	auto it = data.begin();
	for (int i = 0; i < column; ++i)
	{
		vector<GridRectTile*>* tiles = new vector<GridRectTile*>;
		for (int j = 0; j < row; ++j, ++it)
		{
			if (it == data.end())
				return;
			GridRectTile* tile = new GridRectTile();
			tile->Init();
			tile->SetSize({ (*it).width, (*it).height });
			tile->SetPos({ (*it).xPos, (*it).yPos });
			string tileName = (*it).objName;
			tile->SetName(tileName);
			if (tileName.empty())
				tile->SetTexture(nullptr);
			else
			{
				FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
				filePath->SetObjType((FilePathTable::ObjTypes)((int)(*it).objType));
				tile->SetTexture(RESOURCE_MGR->GetTexture(filePath->Get(tileName)));
			}
			tiles->push_back(tile);
		}
		grid.push_back(tiles);
	}; 
}
