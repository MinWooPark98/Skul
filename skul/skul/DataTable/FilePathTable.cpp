#include "FilePathTable.h"
#include "../3rd/rapidcsv.h"

FilePathTable::FilePathTable()
	:DataTable(Types::FilePath), currObj(ObjTypes::Background)
{
	fileNames.push_back("tables/mapeditor/mapeditor_background.csv");
	fileNames.push_back("tables/mapeditor/mapeditor_backobject.csv");
	fileNames.push_back("tables/mapeditor/mapeditor_enemy.csv");
	fileNames.push_back("tables/mapeditor/mapeditor_npc.csv");
	fileNames.push_back("tables/mapeditor/mapeditor_player.csv");
	fileNames.push_back("tables/mapeditor/mapeditor_reward.csv");
	fileNames.push_back("tables/mapeditor/mapeditor_tile.csv");
}

FilePathTable::~FilePathTable()
{
}

void FilePathTable::SetObjType(ObjTypes type)
{
	Release();

	currObj = type;
	rapidcsv::Document doc(fileNames[(int)currObj], rapidcsv::LabelParams(0, -1));
	vector<string> keys = doc.GetColumn<string>(0);
	vector<string> values = doc.GetColumn<string>(1);

	for (int j = 0; j < doc.GetRowCount(); ++j)
	{
		if (table.find(keys[j]) != table.end())
		{
			cout << "value is empty" << endl;
			return;
		}
		table.insert({ keys[j], values[j] });
	}
}

const string& FilePathTable::Get(const string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return "Undefined ID";
	return find->second;
}

void FilePathTable::Release()
{
	table.clear();
}

bool FilePathTable::Load()
{
	SetObjType(currObj);
	return true;
}
