#include "DataTableMgr.h"
#include "LanguageTable.h"
#include "FilePathTable.h"
#include "StatTable.h"

DataTableMgr::DataTableMgr(const DataTableMgr& ref)
{
}

DataTableMgr& DataTableMgr::operator=(const DataTableMgr& ref)
{
    return *this;
}

DataTableMgr::DataTableMgr()
{
    Init();
}

DataTableMgr::~DataTableMgr()
{
    Release();
}

void DataTableMgr::Init()
{
    DataTable* table = new LanguageTable();
    table->Load();
    tables.insert({ DataTable::Types::Language, table });
    
    table = new FilePathTable();
    table->Load();
    tables.insert({ DataTable::Types::FilePath, table });

    table = new StatTable();
    table->Load();
    tables.insert({ DataTable::Types::Stat, table });
}

void DataTableMgr::Release()
{
    for (auto& pair : tables)
    {
        delete pair.second;
    }
    tables.clear();
}