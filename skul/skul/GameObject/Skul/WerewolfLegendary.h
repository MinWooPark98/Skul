#pragma once
#include "Werewolf.h"

class WerewolfLegendary : public Werewolf
{
public:
	WerewolfLegendary();
	virtual ~WerewolfLegendary();

	virtual void Init() override;

	virtual void Idle() { animator->Play("WerewolfLegendaryIdle"); }
	virtual void Move() { animator->Play("WerewolfLegendaryWalk"); }
	virtual void Dash() { animator->Play("WerewolfLegendaryDash"); }
	virtual void Jump() { animator->Play("WerewolfLegendaryJump"); }
	virtual void AttackA() { animator->Play("WerewolfLegendaryAttackA"); }
	virtual void AttackB() { animator->Play("WerewolfLegendaryAttackB"); }
	virtual void JumpAttack() { animator->Play("WerewolfLegendaryJumpAttack"); }
	virtual void Fall() { animator->Play("WerewolfLegendaryFall"); }
	virtual void FallRepeated() { animator->Play("WerewolfLegendaryFallRepeat"); }
	virtual void SkillA();
	virtual void SkillB();

	virtual void SetSkillA(Skills skill) override;
	virtual void SetSkillB(Skills skill) override;
	virtual void SetAnimEvent();
};

