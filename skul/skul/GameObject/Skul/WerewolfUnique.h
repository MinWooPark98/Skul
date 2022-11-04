#pragma once
#include "Werewolf.h"

class WerewolfUnique : public Werewolf
{
public:
	WerewolfUnique();
	virtual ~WerewolfUnique();

	virtual void Init() override;

	virtual void Idle() { animator->Play("WerewolfUniqueIdle"); }
	virtual void Move() { animator->Play("WerewolfUniqueWalk"); }
	virtual void Dash() { animator->Play("WerewolfUniqueDash"); }
	virtual void Jump() { animator->Play("WerewolfUniqueJump"); }
	virtual void AttackA() { animator->Play("WerewolfUniqueAttackA"); }
	virtual void AttackB() { animator->Play("WerewolfUniqueAttackB"); }
	virtual void JumpAttack() { animator->Play("WerewolfUniqueJumpAttack"); }
	virtual void Fall() { animator->Play("WerewolfUniqueFall"); }
	virtual void FallRepeated() { animator->Play("WerewolfUniqueFallRepeat"); }
	virtual void SkillA();
	virtual void SkillB();

	virtual void SetSkillA(Skills skill) override;
	virtual void SetSkillB(Skills skill) override;
	virtual void SetAnimEvent();
};

