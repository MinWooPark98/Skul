#pragma once
#include "SpriteObj.h"
#include "../Framework/Animator.h"

class Player : public SpriteObj
{
public:
	enum class Types
	{
		None = -1,
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
	enum class States
	{
		None = -1,
		Idle,
		Move,
		Dash,
		Jump,
		Fall,
		AttackA,
		AttackB,
		JumpAttack,
	};
protected:
	Types type;
	Tiers tier;
	Animator* skul;

	States currState;

	bool isMoving;
	bool isDashing;
	bool isFloating;
	bool isAttacking;

	int dashCount;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;

	RectangleShape attackBox;

public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;
	
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetState(States newState);

	void UpdateIdle(float dt);
	void UpdateMove(float dt);
	void UpdateDash(float dt);
	void UpdateJump(float dt);
	void UpdateFall(float dt);
	void UpdatAttack(float dt);
};

