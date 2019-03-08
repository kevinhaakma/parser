#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream file;
	ofstream outputFile;
	file.open("special-effects-companies.list");
	outputFile.open("test.txt");

	string line;
	string output;

	if (file.is_open()) {
		while (getline(file, line)) {
			int valCount = 0;
			for (int i = 0; i < line.size(); i++) {

				if (line[i] == '\"' && valCount == 0) {
					valCount++;
					i++;
					while (line[i] != '\"' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}

				if (line[i] == '(' && valCount == 1) {
					valCount++;
					i++;
					while (line[i] != ')' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == '(' && valCount == 0) {
					output += "NULL,";
					valCount++;
				}

				if (line[i] == '{' && valCount == 2) {
					valCount++;
					i++;
					while (line[i] != '}' && i < line.size()) {
						output += line[i ];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == '{' && valCount == 1) {
					output += "NULL,";
					valCount++;
				}

				/*
				if (line[i] == ' ' && valCount == 3) {
					valCount++;
					i++;
					while (line[i] != '[' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == ' ' && valCount == 2) {
					output += "NULL,";
					valCount++;
				}*/
				
				if (line[i] == '[' && valCount == 3) {
					valCount++;
					i++;
					while (line[i] != ']' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == '[' && valCount == 2) {
					output += "NULL,";
					valCount++;
				}
				
				if (line[i] == '(' && valCount == 4) {
					valCount++;
					i++;
					while (line[i] != ')' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == '(' && valCount == 3) {
					output += "NULL,";
					valCount++;
				}
			}
			output += "\n";
		}
		outputFile << output;

	}

	file.close();
	return 0;
}