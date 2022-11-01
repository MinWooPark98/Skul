#pragma once
#include "UiMgr.h"

class PlaySceneUiMgr : public UiMgr
{
public:
	PlaySceneUiMgr(Scene* parentScene);
	virtual ~PlaySceneUiMgr();

	virtual void Init();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

