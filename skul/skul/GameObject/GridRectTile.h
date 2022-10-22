#pragma once
#include "RectTile.h"

class GridRectTile : public RectTile
{
protected:
	const Texture* currTex;

public:
	GridRectTile();
	virtual ~GridRectTile();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void SetTexture(const Texture* tex) override;
};

