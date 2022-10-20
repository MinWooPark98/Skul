#include "DataTableMgr.h"
#include "StringTable.h"

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
    DataTable* table = new StringTable();
    table->Load();
    tables.insert({ DataTable::Types::String, table });
}

void DataTableMgr::Release()
{
    for (auto pair : tables)
    {
        delete pair.second;
    }
    tables.clear();
}