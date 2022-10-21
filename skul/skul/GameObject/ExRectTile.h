#pragma once
#include "RectTile.h"

class ExRectTile : public RectTile
{
public:
	ExRectTile();
	virtual ~ExRectTile();

	virtual void Update(float dt) override;
	function<void(const Texture*)> ClickOn;
};

