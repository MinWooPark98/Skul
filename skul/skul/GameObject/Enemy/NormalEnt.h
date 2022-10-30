#pragma once
#include "Enemy.h"

class NormalEnt : public Enemy
{
protected:
	RayCast* detectingRay;

	float detectRange;
	float attackRange;
	float lastDirX;
	float speed;

	float normalSpeed;
	float chasingSpeed;

	float attackDelay;
	float attackTimer;
	float changeDirDelay;
	float changeDirTimer;

	RectangleShape attackBox;

public:
	NormalEnt();
	virtual ~NormalEnt();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetState(States newState);
	void MeleeAttack();
	void OnCompleteAttack();
};

