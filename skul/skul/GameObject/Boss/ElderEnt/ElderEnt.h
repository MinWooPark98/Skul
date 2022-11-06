#pragma once
#include "../../Object.h"
#include <list>

class Animator;
class Collider;
class SpriteObj;
class ElderEntHead;
class ElderEntJaw;

class ElderEnt : public Object
{
public:
	enum class Phase
	{
		Phase1,
		Phase2,
	};
	enum class States
	{
		Idle,
		NormalStomp,
		Sweep,
		EnergyCorps,
		Groggy,
		WideStomp,
		Dead,
		Invincible,
	};

protected:
	Phase currphase;
	States currState;

	ElderEntHead* head;
	ElderEntJaw* jaw;

	SpriteObj* body;
	list<Collider*> bodyPlatforms;
	Vector2f bodyIdlePos;

	SpriteObj* leftHand;
	Animator* leftHandAnim;
	SpriteObj* rightHand;
	Animator* rightHandAnim;

	list<SpriteObj*> branches;
	list<Animator*> branchAnims;
	list<Collider*> branchPlatforms;

	int totalHp;
	int currHp;

	bool playerHit;

public:
	ElderEnt();
	virtual ~ElderEnt();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;
	virtual void SwitchDevMode() override;

	void SetState(States state);
	void NextPhase();

	void OnHit(int dmg);
};

