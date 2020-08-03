#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <stdio.h>
#include "vertex.h"
using namespace std;




struct vec2 {
	double x;
	double y;
};
vec2 getUV(string str);
vec3 getPos(string line);
vector<int> getIndices(string line);

vector<vec2> getUvs(vector<string> file) {
	vector<vec2> uvs;
	int n = stoi(file.at(0).replace(file.at(0).find("NrVertices:"), sizeof("NrVertices:") - 1, ""));
	cout << "total vertices: " << n << endl;
	for (int i = 1; i <= n; i++) {
		uvs.push_back(getUV(file.at(i)));
	}
	cout << "size uvs: " << uvs.size() << endl;
	
	return uvs;
}


vector<vec2> getUvs(vector<string> file) {
	vector<vec2> uvs;
	int n = stoi(file.at(0).replace(file.at(0).find("NrVertices:"), sizeof("NrVertices:") - 1, ""));
	cout << "total vertices: " << n << endl;
	for (int i = 1; i <= n; i++) {
		uvs.push_back(getUV(file.at(i)));
	}
	cout << "size uvs: " << uvs.size() << endl;
	
	return uvs;
}

vector<string> importFile(string fileName) {
	vector <string> vertex;

	ifstream file(fileName);
	string str;
	while (getline(file, str)) {
		vertex.push_back(str);
	}

	return vertex;
}

void getFile(string filename, ifstream& file)
{
	file.open(filename.c_str());
}

vector<vector<int>> getFaces(const char * filename, FILE * nfgFile) {
	vector<vector<int>> faces;
	
	
	int numindices = 0;
	int numvertices = 0;
	int index;
	//fopen_s(&nfgFile, filename, "r");
	
	fscanf_s(nfgFile, "NrIndices: %d\n", &numindices);
	
	for (int i = 0; i < numindices/3; i++) {
		Vertex vertex;
		int x;
		int y;
		int z;
		fscanf_s(nfgFile, "   %d.    %d,    %d,    %d\n", &index, &x, &y, &z);
		vector<int> f;
		f.push_back(x);
		f.push_back(y);
		f.push_back(z);
		faces.push_back(f);
	}
	cout << "faces size: " << faces.size() << endl;
	return faces;
}

vector<Vertex> getVertices(const char * filename, FILE* nfgFile) {
	vector <Vertex> vertices;
	//FILE* nfgFile;
	int numvertices = 0;
	fscanf_s(nfgFile, "NrVertices: %d\n", &numvertices);
	int index;
	for (int i = 0; i < numvertices; i++) {
		Vertex vertex;
		float x;
		//"   $d. pos:[%lf, 1.020300, -0.083900]; norm:[0.662725, 0.317712, -0.678126]; binorm:[0.014559, 0.899903, 0.435847]; tgt:[-0.748721, 0.298719, -0.591763]; uv:[0.611900, 0.886700];"
		fscanf_s(nfgFile, "   %d. pos:[%lf, %lf, %lf]; norm:[%lf, %lf, %lf]; binorm:[%lf, %lf, %lf]; tgt:[%lf, %lf, %lf]; uv:[%lf, %lf];\n",
			&index,
			&vertex.pos.x,
			&vertex.pos.y,
			&vertex.pos.z,
			&vertex.normal.x,
			&vertex.normal.y,
			&vertex.normal.z,
			&vertex.binormal.x,
			&vertex.binormal.y,
			&vertex.binormal.z,
			&vertex.tangen.x,
			&vertex.tangen.y,
			&vertex.tangen.z,
			&vertex.uv.x,
			&vertex.uv.y
			);
		//cout << vertex.uv.x << " " << vertex.uv.y << endl;
		vertices.push_back(vertex);
	}
	return vertices;
}

 vector <vec3> getVertices(vector<string> file) {
	 vector <vec3> vertices;
	 int n = stoi(file.at(0).replace(file.at(0).find("NrVertices:"), sizeof("NrVertices:") - 1, ""));
	 cout << "total vertices: " << n << endl;
	 for (int i = 1; i <= n; i++) {
		 vertices.push_back(getPos(file.at(i)));
	 }
	 cout << "size vertices: " << vertices.size() << endl;
	 cout << "end";
	 return vertices;
 }

 vector <vector<int>> getFaces(vector<string> file) {
	 vector <vector<int>> indices;
	 int a = stoi(file.at(0).replace(file.at(0).find("NrVertices:"), sizeof("NrVertices:") - 1, "")) + 2;
	 for (int i = a; i < file.size(); i++) {
		 cout << file.at(i) << endl;
		 indices.push_back(getIndices(file.at(i)));
	 }
	 cout << "total faces: " << indices.size() << endl;
	 
	 return indices;
 }

 vector<int> getIndices(string line) {
	 vector <int> verIndex;
	 int index = 0;

	 line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

	 
	 string temp = "";
	 bool begin = false;

	 for (int i = 0; i < line.length(); i++) {
		 
		 if (line[i] == '.') {
	 		 begin = true;
			 temp = "";
			 continue;
		 }
		 if (begin) {
			 
			 if (line[i] == ',') {
				 
				 verIndex.push_back(stoi(temp));
				 temp = "";
			 }
			 else {
				 temp += line[i];
			 }
		 }
		 
	 }
	 
	 verIndex.push_back(stoi(temp));
	 
	 return verIndex;
 }

 vec3 getPos(string str) {
	 vec3 vertices;
	 string a = "";
	 unsigned first = str.find("pos:[")+4;
	 unsigned last = str.find("]");
	 str = str.substr(first, last - first);
	 
	 string d = "";
	 vertices.x = 0.00;
	 vertices.y = 0.00;
	 vertices.z = 0.00;
	 //return vertices;
	 double v[3];
	
	string temp = "";
	int index = 0;
	for (unsigned int i = 1; i < str.length(); i++) {
		if (str[i] == ',') {
			v[index] = stod(temp);
			temp = "";
			index++;
			continue;
		}
		temp += str[i];
	}
	v[index] = stod(temp);
	temp = "";
	 vertices.x = v[0];
	 vertices.y = v[1];
	 vertices.z = v[2];
	 return vertices;
 }

 vec2 getUV(string str) {
	 vec2 vertices;
	 string a = "";
	 unsigned first = str.find("uv:[") + 4;
	 unsigned last = str.find("]");
	 str = str.substr(first, last - first);

	 string d = "";
	 vertices.x = 0.00;
	 vertices.y = 0.00;
	 //return vertices;
	 double v[2];

	 string temp = "";
	 int index = 0;
	 for (unsigned int i = 1; i < str.length(); i++) {
		 if (str[i] == ',') {
			 v[index] = stod(temp);
			 temp = "";
			 index++;
			 continue;
		 }
		 temp += str[i];
	 }
	 v[index] = stod(temp);
	 temp = "";
	 vertices.x = v[0];
	 vertices.y = v[1];
	 
	 return vertices;
 }