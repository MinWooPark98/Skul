#pragma once
#include "DataTable.h"
#include <map>
#include <vector>

class FilePathTable : public DataTable
{
public:
	enum class ObjTypes
	{
		Background,
		Backobject,
		Enemy,
		NPC,
		Player,
		Reward,
		Tile,
		Count,
	};

protected:
	map<string, string> table;
	ObjTypes currObj;

public:
	FilePathTable();
	virtual ~FilePathTable();

	void SetObjType(ObjTypes type);
	const string& Get(const string& id);

	virtual void Release();
	virtual bool Load();

	vector<string> fileNames;
};

