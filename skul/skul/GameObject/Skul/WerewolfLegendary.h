#pragma once
#include "Werewolf.h"

class WerewolfLegendary : public Werewolf
{
public:
	WerewolfLegendary();
	virtual ~WerewolfLegendary();

	virtual void Init() override;

	virtual void Idle() override { animator->Play("WerewolfLegendaryIdle"); }
	virtual void Move() override { animator->Play("WerewolfLegendaryWalk"); }
	virtual void Dash() override;
	virtual void Jump() override;
	virtual void AttackA() override;
	virtual void AttackB() override;
	virtual void JumpAttack() override;
	virtual void Fall() override { animator->Play("WerewolfLegendaryFall"); }
	virtual void FallRepeated() override { animator->Play("WerewolfLegendaryFallRepeat"); }
	virtual void SkillA() override;
	virtual void SkillB() override;

	virtual void SetSkillA(Skills skill) override;
	virtual void SetSkillB(Skills skill) override;
	virtual void SetAnimEvent() override;
};

