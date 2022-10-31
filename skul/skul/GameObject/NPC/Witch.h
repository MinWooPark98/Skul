#pragma 
#include "NPC.h"

class Witch : public NPC
{
public:
	Witch();
	virtual ~Witch();

	virtual void Init() override;
	virtual void Activate() override;
};

