#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream myfile;
	myfile.open("example.txt");

	myfile.close();
	return 0;
}