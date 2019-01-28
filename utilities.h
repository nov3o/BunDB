#include <iostream>
#include <cstring>

using namespace std;

int decLength (int num)
{
	int rowNum;
	for (rowNum = 1; num > 9; rowNum++) num /= 10;
	return rowNum;
}

void printLine (int widths[4])
{
	for (int w = 0; w < 4; w++) {
		cout << '+';
		for (int c = 0; c < widths[w]; c++) cout << '-';
	}
	cout << '+' << endl;
}

bool in (const char* word, const char** array, const int length)
{
	for (int i = 0; i < length; i++)
		if (strcmp(word, array[i]) == 0) return 1;
	return 0;
}

// comps: eq, le, lt, ge, gt, ne(!=), sw(startswith),
//		ew(endswith), in(contains), ni(!in)
// fileds: id, fName, sName, male, age
// Undebugged
void check (const char* field, const char* value)
{
	const char* fields[2] = {"fName", "sName"};
	if (!in(field, fields, 2))
		throw invalid_argument("This field doesn't exist or wrong for this value");
}

void check (const char* field, const int value)
{
	const char* fields[3] = {"id", "male", "age"};
	if (!in(field, fields, 3))
		throw invalid_argument("This field doesn't exist or wrong for this value");
	if (field == "male" && value != 0 && value != 1)
		throw invalid_argument("In normal society there are only two genders");
	if (value < 0)
		throw invalid_argument("Any field of current table can't be negative");
}
