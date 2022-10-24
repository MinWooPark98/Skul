#pragma once
#include "../GameObject/Object.h"

class GridRectTile;

class Grid : public Object
{
protected:
	vector<vector<GridRectTile*>*> grid;

public:
	Grid();
	virtual ~Grid();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	vector<vector<GridRectTile*>*>& Get() { return grid; }
};

