#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct vec3 {
	float x;
	float y;
	float z;
};

 vector<string> importFile(string fileName) {
	vector <string> vertex;

	ifstream file(fileName);
	string str;
	while (getline(file, str)) {
		cout << str << endl;
		vertex.push_back(str);
	}

	return vertex;
}