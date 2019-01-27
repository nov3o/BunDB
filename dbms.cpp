#include <iostream>
#include "bundb.h"

using namespace std;

int main()
{
	int length;
	Person* list = get_table("table", length);
	print(list, length);
	delete [] list;
}
