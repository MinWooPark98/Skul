#pragma once
#include "RectTile.h"

class DragRectTile : public RectTile
{
protected:
	bool isCreated;

public:
	DragRectTile();
	virtual ~DragRectTile();

	virtual void Update(float dt) override;
};

