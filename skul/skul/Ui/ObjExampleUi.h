#pragma once
#include "../GameObject/Object.h"

class ExRectTile;
class ListMoverUi;

class ObjExampleUi : public Object
{
protected:
	vector<ExRectTile*> tiles;
	int currTile;
	ListMoverUi* listMover;

	ExRectTile* clickedTile;
	string tileNames;

public:
	ObjExampleUi();
	virtual ~ObjExampleUi();

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
