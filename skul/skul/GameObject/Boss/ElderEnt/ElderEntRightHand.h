#pragma once
#include "ElderEntHand.h"

class ElderEntRightHand : public ElderEntHand
{
public:
	ElderEntRightHand();
	virtual ~ElderEntRightHand();

	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void ReturnIdlePos() override;
	virtual void ReturnStompPos() override;
	virtual void OnCompleteStomp() override;
};

