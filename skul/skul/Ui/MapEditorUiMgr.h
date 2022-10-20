#pragma once
#include "UiMgr.h"

class MapEditorUiMgr : public UiMgr
{
protected:
public:
	MapEditorUiMgr();
	virtual ~MapEditorUiMgr();

	virtual void Init();

	virtual void Reset();

	virtual void Update(float dt);
};
