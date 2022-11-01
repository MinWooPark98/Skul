#pragma once
#include "PlayScene.h"

class MonsterScene : public PlayScene
{
public:
	MonsterScene();
	virtual ~MonsterScene();
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

