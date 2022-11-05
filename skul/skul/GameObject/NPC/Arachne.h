#pragma once
#include "NPC.h"

class Arachne : public NPC
{
protected:
	Animator* cocoonAnim;

	bool isActive;
	Vector2f evolvingPoint;

public:
	Arachne();
	virtual ~Arachne();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Activate() override;

	void EvolveSkul();
	void OnCompleteEvolve();
	virtual void SetPos(const Vector2f& pos) override;
};

