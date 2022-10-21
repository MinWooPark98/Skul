#pragma once
#include "../GameObject/Object.h"

class GridRectTile;

class GridUi : public Object
{
protected:
	vector<vector<GridRectTile*>*> map;

public:
	GridUi();
	virtual ~GridUi();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

