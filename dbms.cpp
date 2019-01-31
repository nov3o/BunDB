#include <iostream>
#include "bundb.h"

using namespace std;

void load()
{
	Person load[] = {
		{"John", "Doe", 1, 22},
		{"Johana", "Doney", 0, 22},
		{"Cir", "Nobaka", 0, 60},
		{"Gud", "Boi", 1, 12},
		{"Albert", "Einstein", 1, 140},
		{"Reimu", "Hakurei", 0, 14},
		{"Sunn", "Deim", 1, 14},
		{"Ruri", "Gokou", 0, 14},
		{"Rekardo", "Milos", 1, 42},
	};
	fstream file("table", ios::binary|ios::out|ios::trunc);
	file.write((char*)load, sizeof(load));
	file.close();
}

int main()
{
	// load();
	Table table("table"); ////2/
	table.insert("Oleg", "Benedictoxygenipropanol", 1, 99);
	table.print();
	table.drop();
}
