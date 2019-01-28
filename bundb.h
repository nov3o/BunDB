/*
	Here functions' modify status
	Modifies:
		get_table
	Doesn't:
		print
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "utilities.h"

using namespace std;

struct Person
{
	// short id;
	char fName[20];
	char sName[20];
	bool male;
	short age;
};

struct Table{
	Person* rows;
	int length;

	Table(const char*);
	Table();
	~Table();

	Table select(const char*, const char*, bool comp(const char*, const char*));
	Table select(const char*, const int, bool comp(const int, const int));
	void drop();
};

Table::Table(const char* name)
{
	fstream file(name, ios::binary|ios::in);
	file.seekg(0, ios::end);
	length = file.tellg() / sizeof(Person);
	file.seekg(0);
	rows = new Person[length];
	file.read((char*)rows, length*sizeof(Person));
}

Table::Table() { length = 0; }

Table::~Table()
{
	delete [] rows;
}


// comps: eq, le, lt, re, rt, ne(!=),
// 		sw(startswith), ew(endswith), in, ni(not in)
// We can't check validity of functions
Table Table::select (
	const char* field, const char* value, bool comp(const char*, const char*)
	)
{
	check(field, value);
	// For all comps, for only fName and sName fields
	int p;
	Table newTable;
	if (strcmp(field, "fName") == 0) {
		for (int row = 0; row < length; row++)
			if (comp(value, rows[row].fName)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (comp(value, rows[row].fName))
				newTable.rows[np] = rows[row];
	}
	else {
		for (int row = 0; row < length; row++)
			if (comp(value, rows[row].sName)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (comp(value, rows[row].sName))
				newTable.rows[np] = rows[row];
	}
	return newTable; // Change it
}

Table Table::select (
	const char* field, const int value, bool comp(const int, const int)
	)
{
	/*
		s0me c0de
	*/
}

void Table::drop()
{
	delete [] rows;
	length = 0;
}

// This is fake overload; function takes ostream instance, but doesn't use it
// and returns as is. I did it because will have sence to convey instance to
// printLine
ostream& operator << (ostream& out, Table table)
{
	Person* list = table.rows;
	int length = table.length;
	// Setup for |Name|Surname|Sex |Age|
	//           |Name|Surname|Male|Age|
	int widths[4] = {4, 7, 4, 3};
	for (int i = 0; i < length; i++)
	{
		if (strlen(list[i].fName) > widths[0])
			widths[0] = strlen(list[i].fName);
		if (strlen(list[i].sName) > widths[1])
			widths[1] = strlen(list[i].sName);
		if (!list[i].male)
			widths[2] = strlen("female");
		if (decLength(list[i].age) > widths[3])
			widths[3] = decLength(list[i].age);
	}

	printLine(widths);
	cout << '|' << setw(widths[0]) << left << "Name";
	cout << '|' << setw(widths[1]) << left << "Surname";
	cout << '|' << setw(widths[2]) << left << "Sex";
	cout << '|' << setw(widths[3]) << left << "Age";
	cout << '|' << endl;
	printLine(widths);
	printLine(widths);
	for (int r = 0; r < length; r++) {
		cout << '|' << setw(widths[0]) << left << list[r].fName;
		cout << '|' << setw(widths[1]) << left << list[r].sName;
		cout << '|' << setw(widths[2]) << left;
		if (list[r].male) cout << "Male";
		else cout << "Female";
		cout << '|' << setw(widths[3]) << left << list[r].age;
		cout << '|' << endl;
		printLine(widths);
	}
	return out;
}

ostream& operator << (ostream& out, Person pers)
{
	int widths[4] = {strlen(pers.fName), strlen(pers.sName), 4, decLength(pers.age)};
	if (!pers.male) widths[2] = 6;
	printLine(widths);
	cout << "|" << pers.fName << "|" << pers.sName << "|";
	if (pers.male) cout << "Male";
	else cout << "Female";
	cout << "|" << pers.age << "|" << endl;
	printLine(widths);
	return out;
}
