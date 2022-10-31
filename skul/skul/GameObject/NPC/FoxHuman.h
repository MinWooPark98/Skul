#pragma once
#include "NPC.h"

class FoxHuman : public NPC
{
public:
	FoxHuman();
	virtual ~FoxHuman();

	virtual void Init() override;
	virtual void Activate() override;
};

