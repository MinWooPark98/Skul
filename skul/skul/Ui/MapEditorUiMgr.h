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
		BackObject,
		Platform,
		Player,
		Enemies,
		NPC,
		Reward,
		Erase,
	};
protected:
	Texture* currTex;
	
	list<TextButtonUi*> textButtons;
	Modes mode;

public:
	MapEditorUiMgr();
	virtual ~MapEditorUiMgr();

	virtual void Init();

	virtual void Reset();

	virtual void Update(float dt);

	void ChangeMode(TextButtonUi::Modes mode);
};
