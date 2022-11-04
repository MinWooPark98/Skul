#pragma once
#include "Werewolf.h"

class WerewolfRare : public Werewolf
{
public:
	WerewolfRare();
	virtual ~WerewolfRare();

	virtual void Init() override;

	virtual void Idle() { animator->Play("WerewolfRareIdle"); }
	virtual void Move() { animator->Play("WerewolfRareWalk"); }
	virtual void Dash() { animator->Play("WerewolfRareDash"); }
	virtual void Jump() { animator->Play("WerewolfRareJump"); }
	virtual void AttackA() { animator->Play("WerewolfRareAttackA"); }
	virtual void AttackB() { animator->Play("WerewolfRareAttackB"); }
	virtual void JumpAttack() { animator->Play("WerewolfRareJumpAttack"); }
	virtual void Fall() { animator->Play("WerewolfRareFall"); }
	virtual void FallRepeated() { animator->Play("WerewolfRareFallRepeat"); }
	virtual void SkillA();
	virtual void SkillB();

	virtual void SetSkillA(Skills skill) override;
	virtual void SetAnimEvent();
};

