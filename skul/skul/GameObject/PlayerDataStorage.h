#pragma once
#include "Skul/Skul.h"

class PlayerDataStorage
{
public:
	struct SkulData
	{
		Skul::OffensiveTypes offType;
		Skul::Types type;
		Skul::Tiers tier;
	};
private:
	SkulData* mainSkul;
	SkulData* subSkul;
	int totalHp;
	int currHp;
	float speedAdd;
	int attackAdd;

public:
	PlayerDataStorage();
	~PlayerDataStorage();

	void Reset();

	void Save();
	void Load();
};

