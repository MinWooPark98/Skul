#pragma once
#include "UiMgr.h"
#include "TextButtonUi.h"

class MapEditorUiMgr : public UiMgr
{
protected:
	list<TextButtonUi*> textButtons;

public:
	MapEditorUiMgr();
	virtual ~MapEditorUiMgr();

	virtual void Init();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void ResetButton();
};
