#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream file;
	file.open("special-effects-companies.list");
	string tmp;
	int count = 0;
	if (file.is_open()) {
		while (getline(file, tmp)) {
			count++;
		}
		cout << count << endl;
	}

	file.close();
	return 0;
}