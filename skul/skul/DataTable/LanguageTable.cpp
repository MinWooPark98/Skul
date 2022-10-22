#include "LanguageTable.h"
#include "../3rd/rapidcsv.h"

LanguageTable::LanguageTable()
	: DataTable(Types::Language), currentLang(Languages::KOR)
{
	fileNames.push_back("tables/StringTable_Kor.csv");	//
	fileNames.push_back("tables/StringTable_Eng.csv");
	fileNames.push_back("tables/StringTable_Jpn.csv");
}

LanguageTable::~LanguageTable()
{
}

void LanguageTable::SetLanguage(Languages lang)
{
	Release();

	currentLang = lang;
	rapidcsv::Document doc(fileNames[(int)currentLang], rapidcsv::LabelParams(0, -1));
	vector<string> keys = doc.GetColumn<string>(0);		// ID
	vector<string> values = doc.GetColumn<string>(1);	// STRING

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

const string& LanguageTable::Get(const string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return "Undefined ID";
	return find->second;
	//return Get(currentLang, id);
}

//const string& StringTable::Get(Languages lang, const string& id)
//{
//	auto find = table.find(id);
//	if (find == table.end())
//		return "Undefined ID";
//	return find->second;
//}

void LanguageTable::Release()
{
	table.clear();
}

bool LanguageTable::Load()
{
	SetLanguage(currentLang);

	return true;
}