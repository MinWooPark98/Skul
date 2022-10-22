#pragma once
#include "RectTile.h"

class ExRectTile : public RectTile
{
public:
	ExRectTile();
	virtual ~ExRectTile();

	virtual void Update(float dt) override;

	void ClickedOff() { tile->setOutlineColor({ 0, 0, 0, 255 }); }
};
