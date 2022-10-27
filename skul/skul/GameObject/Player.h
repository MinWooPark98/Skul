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
		Attack,
		Fall,
	};
	
protected:
	Skul* mainSkul;
	Skul* subSkul;

	States currState;

	bool isMoving;
	bool isDashing;
	bool isJumping;

	float dashTime;
	float dashTimer;
	float doubleDashableTime;
	float doubleDashTimer;
	float dashDelay;
	float dashDelayTimer;
	int dashCount;
	bool dashAble;
	
	int jumpCount;

	bool isAttacking;

	float speed;
	Vector2f direction;
	float lastDirX;

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
	void UpdateJump(float dt);

	void OnCompleteAttackA();
};

