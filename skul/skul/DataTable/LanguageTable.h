#pragma once
#include "DataTable.h"
#include <map>
#include <vector>

using namespace std;
// map<언어, map<...>>
	// map<아이디, 문자열>

enum class Languages
{
	KOR,
	ENG,
	JPN,
	COUNT,
};

class LanguageTable : public DataTable
{
private:
	//map<Languages, map<string, string>*> tables;

	map<string, string> table;	// 
	Languages currentLang;

public:
	LanguageTable();
	virtual ~LanguageTable();

	void SetLanguage(Languages lang);

	const string& Get(const string& id);
	//const string& Get(Languages lang, const string& id);

	virtual void Release();
	virtual bool Load();

	vector<string> fileNames;
};
