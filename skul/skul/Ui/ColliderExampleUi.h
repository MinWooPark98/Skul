#pragma once
#include "../GameObject/Object.h"
#include <list>

class ExRectTile;

class ColliderExampleUi : public Object
{
public:
	enum class ColliderTypes
	{
		TopSide,
		AllSide,
		Count,
	};
protected:
	list<ExRectTile*> tiles;

	ExRectTile* clickedTile;

public:
	ColliderExampleUi();
	virtual ~ColliderExampleUi();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;
};

