#pragma once
#include "../GameObject/Object.h"

class TriangleTile;

class ListMoverUi : public Object
{
protected:
	TriangleTile* listPrev;
	TriangleTile* listNext;

	float distance;

public:
	ListMoverUi();
	virtual ~ListMoverUi();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;
	void SetDistance(float distance);
	void SetSize(float rad);
};
