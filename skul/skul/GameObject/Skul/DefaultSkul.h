#pragma once
#include "Skul.h"

class DefaultSkul : public Skul
{
public:
	DefaultSkul();
	virtual ~DefaultSkul();

	virtual void Init() override;

	virtual void Idle() override { animator->Play("DefaultSkulIdle"); }
	virtual void Move() override { animator->Play("DefaultSkulWalk"); }
	virtual void Dash() override { animator->Play("DefaultSkulDash"); }
	virtual void Jump() override { animator->Play("DefaultSkulJump"); }
	virtual void AttackA() override { animator->Play("DefaultSkulAttackA"); }
	virtual void AttackB() override { animator->Play("DefaultSkulAttackB"); }
	virtual void JumpAttack() override { animator->Play("DefaultSkulJumpAttack"); }
	virtual void Fall() override { animator->Play("DefaultSkulFall"); }
	virtual void FallRepeated() override { animator->Play("DefaultSkulFallRepeat"); }
};
