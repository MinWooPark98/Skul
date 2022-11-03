#pragma once
#include "DataTable.h"
#include <map>

class StatTable : public DataTable
{
public:
	struct Stat
	{
		float speed;
		int attackDmg;
		int dashableCount;
		
		Stat(float speed, int attackDmg, int dashableCount) :speed(speed), attackDmg(attackDmg), dashableCount(dashableCount) {}
	};

protected:
	map<int, map<int, Stat>> table;

public:
	StatTable();
	virtual ~StatTable();

	const Stat& Get(int offType, int tier);

	virtual void Release();
	virtual bool Load();

	string fileName;
};

