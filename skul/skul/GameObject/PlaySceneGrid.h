#pragma once
#include "Object.h"
#include "MapEditorDataMgr.h"

class PlaySceneGrid : public Object
{
protected:
	vector<RectangleShape*> grid;

public:
	PlaySceneGrid();
	virtual ~PlaySceneGrid();

	virtual void Draw(RenderWindow& window) override;
	void Load(const list<MapEditorDataMgr::MapData>& data);
};
