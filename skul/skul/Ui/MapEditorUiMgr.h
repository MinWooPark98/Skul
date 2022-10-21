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
		Platform,
		Player,
		Enemies,
		NPC,
		Reward,
		Erase,
	};
protected:
	Texture* currTex;

	RectangleShape* exTileFrame;
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
