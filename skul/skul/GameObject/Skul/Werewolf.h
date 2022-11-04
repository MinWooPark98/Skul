#pragma once
#include "Skul.h"

class Werewolf : public Skul
{
public:
	Werewolf();
	virtual ~Werewolf();

	virtual void Init() override;

	virtual void AttackA() override;
	virtual void AttackB() override;
	virtual void JumpAttack() override;

	void Predation();
	void Ripper();
};

