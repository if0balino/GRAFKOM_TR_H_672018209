#pragma once
#pragma once
#include <vector>
#include <iostream>
#include <GL/freeglut.h>
#include "./utils.h"
#include <string>
#include <stdio.h>
#include "vertex.h"
#include "TGA.h"

using namespace std;

class Object {
private:
	vector <Vertex> vertices;
	std::vector <vec3> indices;
	std::vector <std::vector<int>> faces;
	std::vector <vec2> uvs;
	GLuint texture;
	//std::vector <std::tuple<int, int, int>> faces;
	vec3 position;
	vec3 rotation;
public:
	Object() {
	
	}
	void setup(const char * fileLocation, const char* textureLocation) {
		//vector <string> nfg = importFile(fileLocation);
		FILE* nfgFile;
		fopen_s(&nfgFile, fileLocation, "r");
		//Vertex * vertex[];
		///vertices = getVertices(nfg);
		//faces = getFaces(nfg);
		//uvs = getUvs(nfg);
		//ifstream file;
		vertices = getVertices("Woman1.nfg", nfgFile);
		faces = getFaces("Woman1.nfg", nfgFile);

		std::cout << "vertex size: " <<  vertices.size() << std::endl;
		std::cout << "faces size: " << faces.size() << std::endl;
		/*for (int i = 0; i < vertices.size(); i++) {
			cout << i << " " << vertices.at(i).pos.x << " " << vertices.at(i).pos.y << " " << vertices.at(i).pos.z << " " << endl;
		}*/
		texture = loadBMP_custom(textureLocation);

	}
	void draw() {
		glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		glRotatef(1.0f, this->rotation.x, this->rotation.y, this->rotation.z);

		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		for (int i = 0; i < faces.size(); i++) {
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;
			glLineWidth(1);
			glBegin(GL_POLYGON);
			glColor3ub(r, g, b);
			for (int j = 0; j < 3; j++) {
				glTexCoord2d(vertices.at(faces.at(i).at(j)).uv.x, vertices.at(faces.at(i).at(j)).uv.y);
				glVertex3d(
					vertices.at(faces.at(i).at(j)).pos.x,
					vertices.at(faces.at(i).at(j)).pos.y,
					vertices.at(faces.at(i).at(j)).pos.z
					);
			}
			glEnd();
		}
		
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	void update(vec3 pos, vec3 rot) {
		this->position = pos;
		this->rotation = rot;
	}
	void idle() {
		this->rotation.y += 1.0;
	}
};