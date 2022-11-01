#pragma once
#include "PlayScene.h"

class NpcScene : public PlayScene
{
public:
	NpcScene();
	virtual ~NpcScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter() override;
};

