#pragma once
#include <string>

using namespace std;

class DataTable
{
public:
	enum class Types
	{
		None = -1,
		Language,
		FilePath,
		Stat,
	};
private:
	Types type;
	DataTable(const DataTable& ref);
	DataTable& operator = (const DataTable& ref);
public:
	static int TotalTypes;
	DataTable(Types t);

	virtual void Release() = 0;
	virtual bool Load() = 0;
};