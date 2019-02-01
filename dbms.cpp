#include <iostream>
#include "bundb.h"

using namespace std;

// You can use it if you have no table yet
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
		{"Ricardo", "Milos", 1, 42},
	};
	fstream file("table", ios::binary|ios::out|ios::trunc);
	file.write((char*)load, sizeof(load));
	file.close();
}

int main()
{
	// load();

	// DB management example
	Table table("table");
	table.insert("Gregor", "Bthenchik", 1, 27);
	table.del("age", 50, gt);
	table.select("sName", "Do", ns).sort("fName").sort("age", 0).print();
}
