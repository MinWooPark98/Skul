#pragma once
#include "../SpriteObj.h"
#include <list>

class Animator;
class RayCast;

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

public:
	Enemy(Types type);
	virtual ~Enemy();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetState(States newState) = 0;

	void OnCollisionBlock(const FloatRect& blockBound);
};

