#pragma once
#include "Skul.h"
#include <functional>

class SpriteObj;

class DefaultSkul : public Skul
{
protected:
	SpriteObj* head;
	bool isHeadFlying;
	float headSpeed;
	float flyingDuration;
	float flyingTimer;
	float separateTime;
	float separateTimer;

	bool isHeadOn;

	bool enemyCollided;

public:
	DefaultSkul();
	virtual ~DefaultSkul();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SwitchDevMode() override;

	virtual void Idle() override;
	virtual void Move() override;
	virtual void Dash() override;
	virtual void Jump() override;
	virtual void AttackA() override;
	virtual void AttackB() override;
	virtual void JumpAttack() override;
	virtual void Fall() override;
	virtual void FallRepeated() override;
	virtual void SkillA() override;
	virtual void SkillB() override;

	virtual void SetAnimEvent(Player* player);
	virtual void OnCompleteSkillA() override;

	bool HeadOnCollision(const FloatRect& blockBound);
};
