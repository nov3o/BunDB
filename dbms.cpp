#include <iostream>
#include "bundb.h"

using namespace std;

int main()
{
	// First db load for test
/*	Person table[] = {
		{"John", "Doe", 1, 20},
		{"Johana", "Doney", 0, 22}
	};
	fstream file("table", ios::binary|ios::out|ios::trunc);
	file.write((char*)table, sizeof(table));
	*/
	Table table("table");
	cout << table;
	delete [] table.rows;
}
