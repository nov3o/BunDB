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
	table.print(0);
	table.insert("Cir", "Noisbaka", 0, 60);
	table.print(0);
	table.drop();
}
