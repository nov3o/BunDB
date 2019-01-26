#include <fstream>
#include <iostream>

using namespace std;

struct Person;
Person* get_table(const char*);

// 43 bytes each
struct Person
{
	char fName[20];
	char sName[20];
	bool male;
	short age;
} empty;

Person* get_table (const char* name)
{
	int length;
	fstream lengthFile("size");
	lengthFile >> length;
	if (!length) return NULL;
	return &empty;
}
