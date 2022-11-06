#pragma once
#include "PlayScene.h"

class BossScene : public PlayScene
{
public:
	BossScene();
	virtual ~BossScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter() override;
};

