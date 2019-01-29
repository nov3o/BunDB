#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "utilities.h"
// #include "models.h" // Cause it's included in utilities.h

using namespace std;

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

void Table::print (bool fieldNames=1)
{
	if (!length) return;
	int widths[4];
	if (fieldNames)
	{
		widths[0]=4; widths[1]=7; widths[2]=4; widths[3]=3;
	}
	else
	{
		widths[0]=1; widths[1]=1; widths[2]=4; widths[3]=1;
	}
	for (int i = 0; i < length; i++)
	{
		if (strlen(rows[i].fName) > widths[0])
			widths[0] = strlen(rows[i].fName);
		if (strlen(rows[i].sName) > widths[1])
			widths[1] = strlen(rows[i].sName);
		if (!rows[i].male)
			widths[2] = strlen("female");
		if (decLength(rows[i].age) > widths[3])
			widths[3] = decLength(rows[i].age);
	}

	if (fieldNames)
	{
		printLine(widths);
		cout << '|' << setw(widths[0]) << left << "Name";
		cout << '|' << setw(widths[1]) << left << "Surname";
		cout << '|' << setw(widths[2]) << left << "Sex";
		cout << '|' << setw(widths[3]) << left << "Age";
		cout << '|' << endl;
		printLine(widths);
	}
	printLine(widths);
	for (int r = 0; r < length; r++) {
		cout << '|' << setw(widths[0]) << left << rows[r].fName;
		cout << '|' << setw(widths[1]) << left << rows[r].sName;
		cout << '|' << setw(widths[2]) << left;
		if (rows[r].male) cout << "Male";
		else cout << "Female";
		cout << '|' << setw(widths[3]) << left << rows[r].age;
		cout << '|' << endl;
		printLine(widths);
	}
}

// comps: eq, le, lt, ge, gt, ne(!=), sw(startswith), ew(endsw), in, ni(!in)
// We can't check validity of functions
Table Table::select (
	const char* field, const char* value, bool comp(const char*, const char*)
	)
{
	selCheck(field, value);
	// For all comps, for only fName and sName fields
	int p = 0;
	Table newTable;
	if (strcmp(field, "fName") == 0) {
		for (int row = 0; row < length; row++)
			if (comp(value, rows[row].fName)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (comp(value, rows[row].fName))
				newTable.rows[np++] = rows[row];
	}
	else {
		for (int row = 0; row < length; row++)
			if (comp(value, rows[row].sName)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (comp(value, rows[row].sName))
				newTable.rows[np++] = rows[row];
	}
	return newTable;
}

Table Table::select (
	const char* field, const int value, bool comp(const int, const int)
	)
{
	selCheck(field, value);
	// for male, age fields
	// for eq, le, lt, ge, gt, ne(!=) comps
	int p = 0;
	Table newTable;
	// Only for eq, ne comps
	if (strcmp(field, "male") == 0) {
		for (int row = 0; row < length; row++)
			if (comp(value, rows[row].male)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (comp(value, rows[row].male))
				newTable.rows[np++] = rows[row];
	}
	else if (strcmp(field, "age") == 0) {
		for (int row = 0; row < length; row++)
			if (comp(value, rows[row].age)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (comp(value, rows[row].age))
				newTable.rows[np++] = rows[row];
	}
	return newTable;
}

// Just inverted select
Table Table::del (
	const char* field, const char* value, bool comp(const char*, const char*)
	)
{
	selCheck(field, value);
	// For all comps, for only fName and sName fields
	int p = 0;
	Table newTable;
	if (strcmp(field, "fName") == 0) {
		for (int row = 0; row < length; row++)
			if (!comp(value, rows[row].fName)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (!comp(value, rows[row].fName))
				newTable.rows[np++] = rows[row];
	}
	else {
		for (int row = 0; row < length; row++)
			if (!comp(value, rows[row].sName)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (!comp(value, rows[row].sName))
				newTable.rows[np++] = rows[row];
	}
	return newTable;
}

// Just inverted select
Table Table::del (
	const char* field, const int value, bool comp(const int, const int)
	)
{
	selCheck(field, value);
	// for male, age fields
	// for eq, le, lt, ge, gt, ne(!=) comps
	int p = 0;
	Table newTable;
	// Only for eq, ne comps
	if (strcmp(field, "male") == 0) {
		for (int row = 0; row < length; row++)
			if (!comp(value, rows[row].male)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (!comp(value, rows[row].male))
				newTable.rows[np++] = rows[row];
	}
	else if (strcmp(field, "age") == 0) {
		for (int row = 0; row < length; row++)
			if (!comp(value, rows[row].age)) p++;
		newTable.length = p;
		newTable.rows = new Person[p];
		for (int np = 0, row = 0; np < p; row++)
			if (!comp(value, rows[row].age))
				newTable.rows[np++] = rows[row];
	}
	return newTable;
}

void Table::insert (const char* fN, const char* sN, const bool m, const int a)
{
	if (strlen(fN) < 1)
		throw invalid_argument("Name must be at least 1 symbol");
	if (strlen(sN) < 1)
		throw invalid_argument("Surname must be at least 1 symbol");
	if (m != 0 && m != 1)
		throw invalid_argument("Bool sex must be 1 or 0");
	if (a < 1)
		throw invalid_argument("Age cannot be negative or zero");

	Person* newRows = new Person[length+1];
	memcpy(newRows, rows, sizeof(Person)*length);
	strcpy(newRows[length].fName, fN);
	strcpy(newRows[length].sName, sN);
	newRows[length].male = m;
	newRows[length].age = a;
	rows = newRows;
	length++;
}

// In asc male sort first will be Female
Table Table::sort (const char* field, bool asc=1)
{
	sortCheck(field);
	Table tbl = *this;
	bool swapped;
	// Copy-pasting is bad, but I don't know how to perform such action
	// I use bubble sort, because i need to save rows' order in cases where occur
	// same values and it will be efficent in multiple sort queries
	if (field == "fName")
	{
		if (asc)
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = 0; el < length-i-1; el++)
					if (strcmp(tbl.rows[el].fName, tbl.rows[el+1].fName) > 0) {
						swapPers(tbl, el, el+1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
		else
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = length-1; el > 0; el--)
					if (strcmp(tbl.rows[el].fName, tbl.rows[el-1].fName) > 0)
					{
						swapPers(tbl, el, el-1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
	}
	else if (field == "sName")
	{
		if (asc)
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = 0; el < length-i-1; el++)
					if (strcmp(tbl.rows[el].sName, tbl.rows[el+1].sName) > 0) {
						swapPers(tbl, el, el+1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
		else
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = length-1; el > 0; el--)
					if (strcmp(tbl.rows[el].sName, tbl.rows[el-1].sName) > 0)
					{
						swapPers(tbl, el, el-1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
	}
	else if (field == "male")
	{
		if (asc)
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = 0; el < length-i-1; el++)
					if (tbl.rows[el].male > tbl.rows[el+1].male) {
						swapPers(tbl, el, el+1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
		else
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = length-1; el > 0; el--)
					if (tbl.rows[el].male > tbl.rows[el-1].male)
					{
						swapPers(tbl, el, el-1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
	}
	else
	{
		if (asc)
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = 0; el < length-i-1; el++)
					if (tbl.rows[el].age > tbl.rows[el+1].age) {
						swapPers(tbl, el, el+1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
		else
		{
			for (int i = 0; i < length-1; i++)
			{
				swapped = 0;
				for (int el = length-1; el > 0; el--)
					if (tbl.rows[el].age > tbl.rows[el-1].age)
					{
						swapPers(tbl, el, el-1);
						swapped = 1;
					}
				if (!swapped) break;
			}
		}
	}
	return tbl;
}

void Table::drop()
{
	delete [] rows;
	length = 0;
}

ostream& operator<< (ostream& out, Person pers)
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
