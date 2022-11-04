#pragma once
#include "Werewolf.h"

class WerewolfUnique : public Werewolf
{
public:
	WerewolfUnique();
	virtual ~WerewolfUnique();

	virtual void Init() override;

	virtual void Idle() override { animator->Play("WerewolfUniqueIdle"); }
	virtual void Move() override { animator->Play("WerewolfUniqueWalk"); }
	virtual void Dash() override;
	virtual void Jump() override;
	virtual void AttackA() override;
	virtual void AttackB() override;
	virtual void JumpAttack() override;
	virtual void Fall() override { animator->Play("WerewolfUniqueFall"); }
	virtual void FallRepeated() override { animator->Play("WerewolfUniqueFallRepeat"); }
	virtual void SkillA() override;
	virtual void SkillB() override;

	virtual void SetSkillA(Skills skill) override;
	virtual void SetSkillB(Skills skill) override;
	virtual void SetAnimEvent() override;
};

