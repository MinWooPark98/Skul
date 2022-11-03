#pragma once
#include "PlayScene.h"

class MonsterScene : public PlayScene
{
public:
	MonsterScene();
	virtual ~MonsterScene();
	
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter() override;
};

