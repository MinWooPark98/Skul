#pragma 
#include "NPC.h"

class Witch : public NPC
{
protected:
	TextObj* applyingEffect;

	float effectInformTime;
	float effectInformTimer;

	bool isActive;

public:
	Witch();
	virtual ~Witch();

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Activate() override;
};

