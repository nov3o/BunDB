#include <iostream>
#include "bundb.h"

using namespace std;

int main()
{
	Table table("table");
	cout << table;
	delete [] table.rows;
}
