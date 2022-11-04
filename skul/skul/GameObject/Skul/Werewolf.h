#pragma once
#include "Skul.h"

class Werewolf : public Skul
{
public:
	Werewolf();
	virtual ~Werewolf();

	virtual void Init() override;

	void Predation();
	void Ripper();
};

