#include "DataTable.h"

int DataTable::TotalTypes = 1;

DataTable::DataTable(const DataTable& ref)
	:type(Types::None)
{
}

DataTable& DataTable::operator=(const DataTable& ref)
{
	return *this;
}

DataTable::DataTable(Types t)
	:type(t)
{
}
