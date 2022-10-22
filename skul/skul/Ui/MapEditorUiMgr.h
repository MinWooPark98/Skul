#pragma once
#include "UiMgr.h"
#include "TextButtonUi.h"

class MapEditorUiMgr : public UiMgr
{
public:
	enum class Modes
	{
		None = -1,
		BackWall,
		BackObj,
		Player,
		Enemies,
		NPC,
		Reward,
		Tile,
		TileCollider,
		Count,
	};
protected:
	list<TextButtonUi*> textButtons;
	Modes mode;

public:
	MapEditorUiMgr();
	virtual ~MapEditorUiMgr();

	virtual void Init();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void ChangeMode(TextButtonUi::Modes mode);
};
