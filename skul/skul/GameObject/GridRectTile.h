#pragma once
#include "RectTile.h"

class GridRectTile : public RectTile
{
public:
	GridRectTile();
	virtual ~GridRectTile();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void SetTexture(const Texture* tex) override;
};

