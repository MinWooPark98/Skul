#pragma once
#include "../../Framework/Animator.h"
#include "../Object.h"

class Player;

class Skul : public Object
{
public:
	enum class OffensiveTypes
	{
		None = -1,
		Balance,
		Speed,
		Power,
	};
	enum class Types
	{
		Default,
		Werewolf,
	};
	enum class Tiers
	{
		None = -1,
		Normal,
		Rare,
		Unique,
		Legendary,
	};
	enum class Skills
	{
		None = -1,
		SkullThrow,
		Reborn,
		Predation,
		Ripper,
		Count,
	};

protected:
	OffensiveTypes offType;
	Types type;
	Tiers tier;

	Skills skillA;
	Skills skillB;

	vector<Skills> skillSet;

	Animator* animator;
	Player* player;

	const Texture* symbol;
	const Texture* skillAIcon;
	const Texture* skillBIcon;

public:
	Skul(OffensiveTypes offType, Types type, Tiers tier);
	virtual ~Skul();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetTarget(Sprite* playerSprite) { animator->SetTarget(playerSprite); }
	
	virtual void Idle() = 0;
	virtual void Move() = 0;
	virtual void Dash();
	virtual void Jump();
	virtual void AttackA() = 0;
	virtual void AttackB() = 0;
	virtual void JumpAttack() = 0;
	virtual void Fall() = 0;
	virtual void FallRepeated() = 0;
	virtual void SkillA() = 0;
	virtual void SkillB() = 0;

	virtual void SwitchSkul() {}

	void OnCompleteAttackA();
	void OnCompleteAttackB();
	virtual void OnCompleteSkillA() {}
	virtual void OnCompleteSkillB() {}
	void OnCompleteAction();
	function<void()> QuitAttackA;
	function<void()> QuitAttackB;
	function<void()> QuitAction;

	virtual void SetPlayer(Player* player);
	virtual void SetAnimEvent() = 0;
	virtual void SetSkillA(Skills skill) { skillA = skill; }
	virtual void SetSkillB(Skills skill) { skillB = skill; }
	virtual void SetRandomSkillA();
	virtual void SetRandomSkillB();

	void SetSymbol(const Texture* tex) { symbol = tex; }
	const Texture* GetSymbol() const { return symbol; }
	void SetSkillAIcon(const Texture* tex) { skillAIcon = tex; }
	const Texture* GetSkillAIcon() const { return skillAIcon; }
	void SetSkillBIcon(const Texture* tex) { skillBIcon = tex; }
	const Texture* GetSkillBIcon() const { return skillBIcon; }

	OffensiveTypes GetOffType() const{ return offType; }
	Types GetType() const { return type; }
	Tiers GetTier() const { return tier; }
	Skills GetSkillA() const { return skillA; }
	Skills GetSkillB() const { return skillB; }
};

