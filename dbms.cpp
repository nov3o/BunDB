#include <iostream>
#include "bundb.h"

using namespace std;

int main()
{
	// First db load for test
/*	Person load[] = {
		{"John", "Doe", 1, 20},
		{"Johana", "Doney", 0, 22}
	};
	fstream file("table", ios::binary|ios::out|ios::trunc);
	file.write((char*)load, sizeof(load));*/

	Table table("table");
	// Feature: first char[] member of rows[0] becomes null after cout<<(Table) function
	char feature[20];
	strcpy(feature, table.rows[0].fName);
	cout << table;
	strcpy(table.rows[0].fName, feature);
	cout << table.rows[0] << endl;
	table.drop();
}
