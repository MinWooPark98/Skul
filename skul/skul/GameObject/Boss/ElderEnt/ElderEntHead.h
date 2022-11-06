#pragma once
#include "../Boss.h"

class Animator;
class ElderEnt;
class SpriteObj;

class ElderEntHead : public Boss
{
protected:
	SpriteObj* head;
	Animator* headAnim;

	ElderEnt* mainBody;

public:
	ElderEntHead();
	virtual ~ElderEntHead();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;
	void SetMainBody(ElderEnt* body) { mainBody = body; }
	virtual void OnHit(int dmg) override;
};


