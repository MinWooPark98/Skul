#pragma once
#include "../GameObject/Object.h"
#include <list>

class ExRectTile;
class ListMoverUi;

class TileExampleUi : public Object
{
protected:
	vector<list<ExRectTile*>*> tiles;
	int currList;
	ListMoverUi* listMover;

	ExRectTile* clickedTile;
	string tileNames;

public:
	TileExampleUi();
	virtual ~TileExampleUi();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos);
	void SetTileNames(string name) { tileNames = name; }

	void ShowPrevTiles();
	void ShowNextTiles();
};

