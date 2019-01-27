#include <iostream>
#include "bundb.h"

using namespace std;

int main()
{
	Table table;
	table = get_table("table");
	print(table);
	delete [] table.rows;
}
