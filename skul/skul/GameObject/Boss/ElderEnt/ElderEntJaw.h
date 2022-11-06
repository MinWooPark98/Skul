#pragma once
#include "../Boss.h"

class Animator;
class ElderEnt;
class SpriteObj;

class ElderEntJaw : public Boss
{
protected:
	SpriteObj* jaw;
	Animator* jawAnim;

	ElderEnt* mainBody;

public:
	ElderEntJaw();
	virtual ~ElderEntJaw();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;
	void SetMainBody(ElderEnt* body) { mainBody = body; }
	virtual void OnHit(int dmg) override;
};

