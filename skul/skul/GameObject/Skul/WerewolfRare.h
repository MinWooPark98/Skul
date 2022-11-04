#pragma once
#include "Werewolf.h"

class WerewolfRare : public Werewolf
{
public:
	WerewolfRare();
	virtual ~WerewolfRare();

	virtual void Init() override;

	virtual void Idle() override { animator->Play("WerewolfRareIdle"); }
	virtual void Move() override { animator->Play("WerewolfRareWalk"); }
	virtual void Dash() override;
	virtual void Jump() override;
	virtual void AttackA() override;
	virtual void AttackB() override;
	virtual void JumpAttack() override;
	virtual void Fall() override { animator->Play("WerewolfRareFall"); }
	virtual void FallRepeated() override { animator->Play("WerewolfRareFallRepeat"); }
	virtual void SkillA() override;
	virtual void SkillB() override;

	virtual void SetSkillA(Skills skill) override;
	virtual void SetAnimEvent() override;
};

