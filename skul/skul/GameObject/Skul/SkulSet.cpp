#include "SkulSet.h"
#include "DefaultSkul.h"
#include "WerewolfNormal.h"

SkulSet::SkulSet()
{
}

SkulSet::~SkulSet()
{
}

void SkulSet::Init()
{
	{
		map<Skul::Tiers, Skul*>* defaultSkul = new map<Skul::Tiers, Skul*>;
		defaultSkul->insert({ Skul::Tiers::Normal, new DefaultSkul() });
		skulSet.insert({ Skul::Types::Default, defaultSkul });
	}
	{
		map<Skul::Tiers, Skul*>* werewolf = new map<Skul::Tiers, Skul*>;
		werewolf->insert({ Skul::Tiers::Normal, new WerewolfNormal() });
		// werewolf->insert({ Skul::Tiers::Rare, new WerewolfRare() });
		// werewolf->insert({ Skul::Tiers::Unique, new WerewolfUnique() });
		// werewolf->insert({ Skul::Tiers::Legendary, new WerewolfLegendary() });
		skulSet.insert({ Skul::Types::Werewolf, werewolf });
	}
	for (auto& skuls : skulSet)
	{
		for (auto& skul : *skuls.second)
		{
			skul.second->Init();
		}
	}
}

void SkulSet::Reset()
{
	for (auto& skuls : skulSet)
	{
		for (auto& skul : *skuls.second)
		{
			skul.second->Reset();
		}
	}
}
