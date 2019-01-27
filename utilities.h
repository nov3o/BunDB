#include <iostream>

using namespace std;

// Debugged
int decLength(int num) {
	int rowNum;
	for (rowNum = 1; num > 9; rowNum++) num /= 10;
	return rowNum;
}

// Undebugged
void printLine(int widths[4]) {
	for (int w = 0; w < 4; w++) {
		cout << '+';
		for (int c = 0; c < widths[w]; c++) cout << '-';
	}
	cout << '+' << endl;
}
