#include "StatTable.h"
#include "../3rd/rapidcsv.h"

StatTable::StatTable()
	:DataTable(Types::Stat)
{
	fileName = "tables/playerstat.csv";
}

StatTable::~StatTable()
{
}

const StatTable::Stat& StatTable::Get(int offType, int tier)
{
	auto tableElem = table.find(offType);
	if (tableElem == table.end())
		throw "Wrong OffensiveType";
	auto find = tableElem->second.find(tier);
	if(find == tableElem->second.end())
		throw "Wrong Tier";
	return find->second;
}

void StatTable::Release()
{
}

bool StatTable::Load()
{
	Release();

	rapidcsv::Document doc(fileName, rapidcsv::LabelParams(0, -1));
	vector<int> offensiveTypes = doc.GetColumn<int>(0);
	vector<int> tiers = doc.GetColumn<int>(1);
	vector<float> speed = doc.GetColumn<float>(2);
	vector<int> attackDmg = doc.GetColumn<int>(3);
	vector<int> dashableCount = doc.GetColumn<int>(4);

	for (int j = 0; j < doc.GetRowCount(); ++j)
	{
		if (table.find(offensiveTypes[j]) != table.end())
		{
			if (table[offensiveTypes[j]].find(tiers[j]) != table[offensiveTypes[j]].end())
			{
				cout << "value is empty" << endl;
				return false;
			}
			table[offensiveTypes[j]].insert({ tiers[j], { speed[j], attackDmg[j], dashableCount[j] } });
			continue;
		}
		table.insert({ offensiveTypes[j], map<int, Stat>() });
		table[offensiveTypes[j]].insert({ tiers[j], { speed[j], attackDmg[j], dashableCount[j] } });
	}
	return true;
}
