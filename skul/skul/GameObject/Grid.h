#pragma once
#include "../GameObject/Object.h"
#include "MapEditorDataMgr.h"

class GridRectTile;

class Grid : public Object
{
protected:
	vector<vector<GridRectTile*>*> grid;

public:
	Grid();
	virtual ~Grid();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Load(const list<MapEditorDataMgr::MapData>& data);

	vector<vector<GridRectTile*>*>& Get() { return grid; }
};

