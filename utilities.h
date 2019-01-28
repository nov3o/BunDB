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
	const char* fields[2] = {"male", "age"};
	if (!in(field, fields, 2))
		throw invalid_argument("This field doesn't exist or wrong for this value");
	if (field == "male" && value != 0 && value != 1)
		throw invalid_argument("In normal society there are only two genders");
	if (value < 0)
		throw invalid_argument("int/bool field of current table can't be negative");
}

// comps: eq, le, lt, ge, gt, ne(!=), sw(startswith),
//		ew(endswith), in(contains), ni(!in)

// For all comps: bool <comp> (<val>, <row member's val>)
bool eq (const char* a, const char* b) { return !strcmp(b, a); }
bool ne (const char* a, const char* b) { return strcmp(b, a); }
bool le (const char* a, const char* b) { return strcmp(b, a) < 1; }
bool lt (const char* a, const char* b) { return strcmp(b, a) < 0; }
bool ge (const char* a, const char* b) { return strcmp(b, a) > -1; }
bool gt (const char* a, const char* b) { return strcmp(b, a) > 0; }
bool sw (const char* a, const char* b)
{
	if (strlen(b) < strlen(a)) return 0;
	for (int i = 0; i < strlen(a); i++)
		if (b[i] != a[i]) return 0;
	return 1;
}
bool ew (const char* a, const char* b)
{
	if (strlen(b) < strlen(a)) return 0;
	int al = strlen(a);
	int bl = strlen(b);
	for (int i = 0; i < strlen(a); i++)
	{
		cout << a[al-1-i] << b[bl-1-i] << endl;
		if (b[bl-1-i] != a[al-1-i]) return 0;
	}
	return 1;
}
bool in (const char* a, const char* b)
{
	int len = strlen(b);
	for (int i = 0; i < strlen(a)-len; i++)
		if (sw(a, b++)) return 1;
	b -= strlen(a)-len;
	return 0;
}
bool ni (const char* a, const char* b) { return !in(a, b); }

bool eq (const int a, const int b) { return a == b; }
bool ne (const int a, const int b) { return a != b; }
bool le (const int a, const int b) { return b <= a; }
bool lt (const int a, const int b) { return b < a; }
bool ge (const int a, const int b) { return b >= a; }
bool gt (const int a, const int b) { return b > a; }
