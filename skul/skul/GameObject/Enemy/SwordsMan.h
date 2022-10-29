#pragma once
#include "Enemy.h"

class SwordsMan : public Enemy
{
protected:
	RayCast* detectRange;

	float lastDirX;
	float speed;

	float attackDelay;
	float attackTimer;
	float changeDirDelay;
	float changeDirTimer;

	RectangleShape attackBox;

public:
	SwordsMan();
	virtual ~SwordsMan();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetState(States newState);
	void MeleeAttack();
	void OnCompleteAttack();
};

