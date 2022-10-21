#pragma once
#include "../GameObject/Object.h"
#include <list>

class Tile;

class TileExampleUi : public Object
{
protected:
	list<Tile*> tiles;

public:
	TileExampleUi();
	virtual ~TileExampleUi();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

