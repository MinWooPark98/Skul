#pragma once
#include "SpriteObj.h"

class Skul;

class Player : public SpriteObj
{
public:
	enum class States
	{
		None = -1,
		Idle,
		Move,
		Dash,
		Jump,
		AttackA,
		AttackB,
		JumpAttack,
	};
	
protected:
	Skul* mainSkul;
	Skul* subSkul;

	States currState;

	bool isMoving;
	bool isDashing;
	bool isJumping;
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

	void SetSkul(Skul* skul);

	void SetState(States newState);

	void UpdateIdle(float dt);
	void UpdateMove(float dt);
	void UpdateDash(float dt);
	void UpdateJump(float dt);
	void UpdatAttack(float dt);
};

