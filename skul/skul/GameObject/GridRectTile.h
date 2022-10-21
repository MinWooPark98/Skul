#pragma once
#include "RectTile.h"

class GridRectTile : public RectTile
{
public:
	GridRectTile();
	virtual ~GridRectTile();

	virtual void Update(float dt) override;
};

