#pragma once
#include "NPC.h"

class Ogre : public NPC
{
public:
	Ogre();
	~Ogre();

	virtual void Init() override;
	virtual void Activate() override;
};

