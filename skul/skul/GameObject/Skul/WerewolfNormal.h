#pragma once
#include "Werewolf.h"

class WerewolfNormal : public Werewolf
{
public:
	WerewolfNormal();
	virtual ~WerewolfNormal();

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Idle() override { animator->Play("WerewolfNormalIdle"); }
	virtual void Move() override { animator->Play("WerewolfNormalWalk"); }
	virtual void Dash() override;
	virtual void Jump() override;
	virtual void AttackA() override;
	virtual void AttackB() override;
	virtual void JumpAttack() override;
	virtual void Fall() override { animator->Play("WerewolfNormalFall"); }
	virtual void FallRepeated() override { animator->Play("WerewolfNormalFallRepeat"); }
	virtual void SkillA() override;
	virtual void SkillB() override;

	virtual void SetSkillA(Skills skill) override;
	virtual void SetAnimEvent() override;
};

