#pragma once
#include "ElderEntHand.h"

class ElderEntLeftHand : public ElderEntHand
{
public:
	ElderEntLeftHand();
	virtual ~ElderEntLeftHand();

	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void ReturnIdlePos() override;
	virtual void ReturnStompPos() override;
	virtual void OnCompleteStomp() override;
};

