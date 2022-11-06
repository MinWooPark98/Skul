#pragma once
#include "../../SpriteObj.h"

class Animator;
class ElderEnt;

class ElderEntJaw : public SpriteObj
{
protected:
	Animator* jawAnim;

	ElderEnt* mainBody;

public:
	ElderEntJaw();
	virtual ~ElderEntJaw();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void SetMainBody(ElderEnt* body) { mainBody = body; }
	void OnHit(int dmg);
};

