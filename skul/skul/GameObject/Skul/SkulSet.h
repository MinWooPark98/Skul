#pragma once
#include "Skul.h"
#include <map>

using namespace std;

class SkulSet
{
protected:
	map<Skul::Types, map<Skul::Tiers, Skul*>*> skulSet;

public:
	SkulSet();
	~SkulSet();

	void Init();
	void Reset();
	bool Evolvable(Skul* skul);
	Skul* Get(Skul::Types type, Skul::Tiers tier) { return (*skulSet[type])[tier]; }
};
