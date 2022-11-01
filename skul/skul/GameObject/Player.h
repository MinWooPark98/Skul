#pragma once
#include "SpriteObj.h"
#include <functional>

class Skul;
class RayCast;

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
		SkillA,
		SkillB,
	};
	
protected:
	Skul* mainSkul;
	Skul* subSkul;

	vector<RayCast*> rays;

	States currState;

	float normalSpeed;
	float dashSpeed;

	bool isMoving;
	bool isDashing;
	bool isJumping;
	bool jumpingDown;

	float dashTime;
	float dashTimer;
	float doubleDashableTime;
	float doubleDashTimer;
	float dashDelay;
	float dashDelayTimer;
	int dashCount;
	bool dashAble;
	
	int jumpCount;
	int jumpableCount;

	bool isAttacking;

	float speed;
	float lastDirX;

	RectangleShape attackBox;
	int attackDmg;

	int totalHp;
	int currHp;

	Object* platform;

public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;
	
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SwitchDevMode() override;

	void SetSkul(Skul* skul);
	void SetState(States newState);
	void SetBoxes();

	void SetNormalSpeed(float speed) { normalSpeed = speed; }
	float GetNormalSpeed() const { return normalSpeed; }
	void SetDashSpeed(float speed) { dashSpeed = speed; }
	float GetDashSpeed() const { return dashSpeed; }
	void SetJumpableCount(int count) { jumpableCount = count; }
	int SetJumpableCount() const { return jumpableCount; }
	void SetAttackDmg(int dmg) { attackDmg = dmg; }
	int GetAttackDmg() const { return attackDmg; }
	float GetHpRatio() const { return (float)currHp / totalHp; }

	void OnCompleteAttackA();
	void OnCompleteAttackB();

	const Vector2f& GetDirection() const { return direction; }
	float GetLastDirX() const { return lastDirX; }
	Object* GetPlatform() const { return platform; }
	void OnCollisionBlock(const FloatRect& blockBound);

	const Skul* GetMainSkul() const { return mainSkul; }

	function<void()> ResetPlayerUi;

	RectangleShape& GetAttackBox() { return attackBox; }
	void MeleeAttack();
	void OnHit(int dmg);
};

