#pragma once
#include "UiMgr.h"

class MonsterSceneUiMgr : public UiMgr
{
public:
	MonsterSceneUiMgr();
	virtual ~MonsterSceneUiMgr();

	virtual void Init();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

