#pragma once
#include "../../Framework/Animator.h"
#include "../Object.h"

class Player;

class Skul : public Object
{
public:
	enum class Types
	{
		Default,
		Werewolf,
	};
	enum class Tiers
	{
		Normal,
		Rare,
		Unique,
		Legendary,
	};

protected:
	Types type;
	Tiers tier;

	Animator* animator;
	Player* player;

	const Texture* symbol;
	const Texture* skillAIcon;
	const Texture* skillBIcon;

public:
	Skul(Types type, Tiers tier);
	virtual ~Skul();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetTarget(Sprite* playerSprite) { animator->SetTarget(playerSprite); }
	
	virtual void Idle() = 0;
	virtual void Move() = 0;
	virtual void Dash() = 0;
	virtual void Jump() = 0;
	virtual void AttackA() = 0;
	virtual void AttackB() = 0;
	virtual void JumpAttack() = 0;
	virtual void Fall() = 0;
	virtual void FallRepeated() = 0;
	virtual void SkillA() = 0;
	virtual void SkillB() = 0;

	void OnCompleteAttackA();
	void OnCompleteAttackB();
	virtual void OnCompleteSkillA() {}
	virtual void OnCompleteSkillB() {}
	void OnCompleteAction();
	function<void()> QuitAttackA;
	function<void()> QuitAttackB;
	function<void()> QuitAction;

	virtual void SetPlayer(Player* player) { this->player = player; }
	virtual void SetAnimEvent(Player* player) = 0;

	void SetSymbol(const Texture* tex) { symbol = tex; }
	const Texture* GetSymbol() const { return symbol; }
	void SetSkillAIcon(const Texture* tex) { skillAIcon = tex; }
	const Texture* GetSkillAIcon() const { return skillAIcon; }
	void SetSkillBIcon(const Texture* tex) { skillBIcon = tex; }
	const Texture* GetSkillBIcon() const { return skillBIcon; }

	Types GetType() const { return type; }
	Tiers GetTier() const { return tier; }
};

