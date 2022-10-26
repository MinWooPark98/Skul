#pragma once
#include "../../Framework/Animator.h"
#include "../Object.h"

class Skul : public Object
{
public:
	enum class Types
	{
		Default,
		Werewolf,
	};
	enum class Tiers
	{
		Normal,
		Rare,
		Unique,
		Legendary,
	};

protected:
	Types type;
	Tiers tier;

	Animator* animator;

public:
	Skul(Types type, Tiers tier);
	virtual ~Skul();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetTarget(Sprite* playerSprite) { animator->SetTarget(playerSprite); }
	
	virtual void Idle() = 0;
	virtual void Move() = 0;
	virtual void Dash() = 0;
	virtual void Jump() = 0;
	virtual void AttackA() = 0;
	virtual void AttackB() = 0;
	virtual void JumpAttack() = 0;
	virtual void Fall() = 0;
	virtual void FallRepeated() = 0;
};

