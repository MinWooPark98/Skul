#pragma once
#include "SpriteObj.h"

class Animator;
class RayCast;

class Enemy : public SpriteObj
{
public:
	enum class Types
	{
		None,
		Sword,
	};

protected:
	Types type;

	Animator* animator;
	vector<RayCast*> underFeetRays;

	bool playerDetected;
	vector<RayCast*> detectRay;

public:
	Enemy();
	virtual ~Enemy();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

