#include "PlaySceneGrid.h"
#include "../DataTable/FilePathTable.h"
#include "../DataTable/DataTableMGR.h"
#include "../Framework/ResourceMgr.h"

PlaySceneGrid::PlaySceneGrid()
{
}

PlaySceneGrid::~PlaySceneGrid()
{
}

void PlaySceneGrid::Load(const list<MapEditorDataMgr::MapData>& data)
{
	auto it = data.begin();
	while (it != data.end())
	{
		RectangleShape* tile = new RectangleShape();
		tile->setSize({ 32.f, 32.f });
		tile->setPosition({ (*it).xPos, (*it).yPos });
		string tileName = (*it).objName;
		if (tileName.empty())
		{
			tile->setTexture(nullptr);
			tile->setFillColor({ 255, 255, 255, 0 });
		}
		else
		{
			FilePathTable* filePath = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
			filePath->SetObjType((FilePathTable::ObjTypes)((int)(*it).objType));
			tile->setTexture(RESOURCE_MGR->GetTexture(filePath->Get(tileName)));
		}
		grid.push_back(tile);
		++it;
	}
}

void PlaySceneGrid::Draw(RenderWindow& window)
{
	for (auto& tile : grid)
	{
		window.draw(*tile);
	}
}
