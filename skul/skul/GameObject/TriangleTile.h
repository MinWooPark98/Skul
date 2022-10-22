#pragma once
#include "Tile.h"

class TriangleTile : public Tile
{
protected:
	float clickDelay;
	float clickTimer;

public:
	TriangleTile();
	virtual ~TriangleTile();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Update(float dt) override;

	void SetSize(float rad) { ((CircleShape*)tile)->setRadius(rad); }
	float GetSize() const { return ((CircleShape*)tile)->getRadius(); }

	function<void()> ClickOn;
};

