#pragma once
#include "../SpriteObj.h"
#include <list>

class Animator;
class RayCast;
class EnemyHpBarUi;

class Enemy : public SpriteObj
{
public:
	enum class Types
	{
		None,
		SwordsMan,
	};
	enum class States
	{
		None = -1,
		Idle,
		Move,
		Attack,
		Hit,
	};

protected:
	Types type;
	States currState;

	Animator* animator;
	vector<RayCast*> rays;
	Object* platform;

	bool playerDetected;

	float stiffDuration;
	float stiffTimer;
	float stiffDistance;

	int totalHp;
	int currHp;
	EnemyHpBarUi* hpBar;

	int attackDmg;

public:
	Enemy(Types type);
	virtual ~Enemy();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	Object* GetPlatform() const { return platform; }

	virtual void SetState(States newState) = 0;
	void SetPlayerDetected(bool detected) { playerDetected = detected; }
	
	int GetTotalHp() const { return totalHp; }
	int GetCurrHp() const { return currHp; }

	void OnCollisionBlock(const FloatRect& blockBound);
	void OnHit(int dmg);
};

