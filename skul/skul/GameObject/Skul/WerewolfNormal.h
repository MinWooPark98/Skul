#pragma once
#include "Skul.h"

class WerewolfNormal : public Skul
{
public:
	enum class Skills
	{
		None = -1,
		Predation,
		Ripper,
		Count,
	};
protected:
	Skills skill;

public:
	WerewolfNormal();
	virtual ~WerewolfNormal();

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Idle() { animator->Play("WerewolfNormalIdle"); }
	virtual void Move() { animator->Play("WerewolfNormalWalk"); }
	virtual void Dash() { animator->Play("WerewolfNormalDash"); }
	virtual void Jump() { animator->Play("WerewolfNormalJump"); }
	virtual void AttackA() { animator->Play("WerewolfNormalAttackA"); }
	virtual void AttackB() { animator->Play("WerewolfNormalAttackB"); }
	virtual void JumpAttack() { animator->Play("WerewolfNormalJumpAttack"); }
	virtual void Fall() { animator->Play("WerewolfNormalFall"); }
	virtual void FallRepeated() { animator->Play("WerewolfNormalFallRepeat"); }
	virtual void SkillA();
	virtual void SkillB();

	virtual void SetAnimEvent();

	void Predation();
	void Ripper();
};

