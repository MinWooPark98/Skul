#pragma once
#include "../../SpriteObj.h"

class Animator;
class ElderEnt;

class ElderEntHead : public SpriteObj
{
protected:
	Animator* headAnim;

	ElderEnt* mainBody;

public:
	ElderEntHead();
	virtual ~ElderEntHead();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void SetMainBody(ElderEnt* body) { mainBody = body; }
	void OnHit(int dmg);
};


