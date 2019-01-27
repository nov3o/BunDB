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
	char fName[20];
	char sName[20];
	bool male;
	short age;
};

struct Table{
	Person* rows;
	int length;
	void del()
	{
		delete [] rows;
		length = 0;
	}

	~Table()
	{
		delete [] rows;
	}
};

// Returns it's length and changes Person pointer
Table get_table (const char* name)
{
	fstream file(name, ios::binary|ios::in);
	file.seekg(0, ios::end);
	int length = file.tellg() / sizeof(Person);
	file.seekg(0);
	Person* array = new Person[length];
	file.read((char*)array, length*sizeof(Person));
	Table table = {array, length};
	return table;
}

void print(Table table)
{
	Person* list = table.rows;
	int length = table.length;
	// Setup for "|Name|Surname|Sex |Age|"
	// Setup for "|Name|Surname|Male|Age|"
	int widths[4] = {4, 7, 4, 3};
	for (int i = 0; i < length; i++)
	{
		if (strlen(list[i].fName) > widths[0]) widths[0] = strlen(list[i].fName);
		if (strlen(list[i].sName) > widths[1]) widths[1] = strlen(list[i].sName);
		if (!list[i].male) widths[2] = strlen("female");
		if (decLength(list[i].age) > widths[3]) widths[3] = decLength(list[i].age);
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
}
