#pragma once
#include "../GameObject/Object.h"
#include <list>

class RectTile;

class TileExampleUi : public Object
{
protected:
	list<RectTile*> tiles;

public:
	TileExampleUi();
	virtual ~TileExampleUi();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos);
};

