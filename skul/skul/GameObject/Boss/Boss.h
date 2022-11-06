#pragma once
#include "../Object.h"

class Boss : public Object
{
public:
	Boss();
	virtual ~Boss();

	virtual void OnHit(int dmg) = 0;
};

