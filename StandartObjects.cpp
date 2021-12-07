#include "StandartObjects.h"
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

std::vector<Vertex> cubeVertices = {
		{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, //1
		{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, //2
		{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, //3
		{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, //0
		{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, //1
		{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(1.0f, 1.0f)}, //2
		{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},//0
};

std::vector<GLuint> indicesCube =
{
	0, 1, 2, // Upper triangle
	0, 3, 2, // Lower triangle
	0, 4, 1,
	4, 1, 5,
	0, 4, 3,
	4, 3, 7,
	3, 7, 2,
	2, 7, 6,
	4, 5, 6,
	4, 7, 6,
	1, 2, 5,
	2, 5, 6
};

std::vector<Vertex> octaedrVertices = {
	{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, //0
	{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, //1
	{glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, //2
	{glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, //3
	{glm::vec3(0.0f, GLfloat(sqrt(2)), 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	{glm::vec3(0.0f, GLfloat(-sqrt(2)), 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

std::vector<GLuint> indicesOctaedr = {
	0, 1, 2,
	0, 3, 2,
	0, 4, 1,
	1, 4, 2,
	2, 4, 3,
	3, 4, 0,
	0, 5, 1,
	1, 5, 2,
	2, 5, 3,
	3, 5, 0
};


Cube::Cube() : Mesh(cubeVertices, indicesCube) {

}

Octaedr::Octaedr() : Mesh(octaedrVertices, indicesOctaedr) {

}

Torus::Torus(vector<Vertex>& vertices, vector<GLuint>& indices)
	: Mesh(vertices, indices ) {}

Torus BuildTorus(GLfloat radius_XY, GLfloat radius_YZ) {
	//variables in radians
	/*GLfloat u = 0.0f, v = 0.0f;*/
	//center
	glm::vec3 C(0.0f, 0.0f, 0.0f);
	
	vector<Vertex> vertices;
	vector<GLuint> indices;
	
	GLfloat step = 10.0f;

	cout << glm::radians(360.0f) << endl;

	//create vertices
	for (GLfloat u = 0.0f; u < glm::radians(360.0f); u += glm::radians(step)) {
		glm::vec3 W(cos(u), sin(u), 0);
		for (GLfloat v = 0.0f; v < glm::radians(360.0f); v += glm::radians(step)) {
			glm::vec3 curPosition = C +
				(radius_XY * W) +
				(radius_YZ * cos(v) * W) +
				glm::vec3(0, 0, radius_YZ * sin(v));
			glm::vec3 curColor(curPosition);
			curColor = (glm::normalize(curColor));
			glm::vec2 curTexture(0.0f, 0.0f);
			//cout << curPosition.x << " " << curPosition.y << " " << curPosition.z << "\n";
			vertices.push_back({ curPosition, curColor, curTexture });
		}
	}

	GLuint stepToNextU = 360 / step;
	cout << stepToNextU << "\n";
	//indices.push_back(0);
	//indices.push_back(1);
	//indices.push_back(12);
	//indices.push_back(1);
	//indices.push_back(2);
	//indices.push_back(13);
	///*indices.push_back(12);
	//indices.push_back(1);
	//indices.push_back(13);*/
	//indices.push_back(13);
	//indices.push_back(2);
	//indices.push_back(14);


	for (unsigned int i = 0; i < (vertices.size() - stepToNextU - 1); i++) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + stepToNextU);
		indices.push_back(i + 1);
		indices.push_back(i + stepToNextU);
		indices.push_back(i + 1 + stepToNextU);
	}


	/*indices.push_back(1);
	indices.push_back(2);
	indices.push_back(14);*/

	//cout << vertices[13].position.x << " " << vertices[13].position.y << " " << vertices[13].position.z << "\n";
	//cout << vertices[1].position.x << " " << vertices[1].position.y << " " << vertices[1].position.z << "\n";
	//cout << vertices[12].position.x << " " << vertices[12].position.y << " " << vertices[12].position.z << "\n";

	return Torus(vertices, indices);
}

Mesh BuildGraph(double (*func)(double, double), double limitX, double limitY, double h) {
	vector<Vertex> res;
	vector<GLuint> indices;

	unsigned int  stepToNext = round(limitX/h);

	for (double X = -limitX; X < limitX; X += h) {
		//cout << "YES " << X << "\n";
		for (double Y = -limitY; Y < limitY; Y += h) {
			double Z = 0.0f;
			try {
				Z = func(X, Y);
			}
			catch (out_of_range exp) {
				//cout << "WTF";
				continue;
			}
			glm::vec3 curPos(X, Y, Z);
			//cout << curPos.x << " " << curPos.y << " " << curPos.z << "\n";
			glm::vec3 curColor(glm::normalize(curPos));
			glm::vec2 curTex(0.0f, 0.0f);
			res.push_back({ curPos, curColor, curTex });
		}
	}

	
	//
	//stepToNext
	for (unsigned int i = 0; i < (stepToNext * stepToNext - stepToNext); i += stepToNext) {
		for (unsigned int j = 1; j < stepToNext; j++) {
			//triangle 1

			indices.push_back(i + j - 1);
			indices.push_back(i + j);
			indices.push_back(i + stepToNext + j - 1);
			//cout << i + j << " " << i + stepToNext + j - 1 << " " << i + stepToNext + j << "\n";
			//triange 2
			indices.push_back(i + stepToNext + j - 1);
			indices.push_back(i + j);
			indices.push_back(i + stepToNext + j);
			//cout << i + j - 1 << " " << i + j << " " << i + stepToNext + j << "\n";
		}
	}

	for (unsigned int i = stepToNext*stepToNext; i < 2*(stepToNext * stepToNext - stepToNext); i += stepToNext) {
		for (unsigned int j = 1; j < stepToNext; j++) {
			//triangle 1

			indices.push_back(i + j - 1);
			indices.push_back(i + j);
			indices.push_back(i + stepToNext + j - 1);
			//cout << i + j << " " << i + stepToNext + j - 1 << " " << i + stepToNext + j << "\n";
			//triange 2
			indices.push_back(i + stepToNext + j - 1);
			indices.push_back(i + j);
			indices.push_back(i + stepToNext + j);
			//cout << i + j - 1 << " " << i + j << " " << i + stepToNext + j << "\n";
		}
	}




	cout << res.size() << endl;
	return Mesh(res, indices);
}


Mesh GenerateAxis(double limitXY, double limitZ) {
	vector<Vertex> vertices;
	vector<GLuint> indices;
	limitXY += limitXY / 2;
	limitZ += limitZ / 2;
	glm::vec3 color(0.0f);
	glm::vec2 texCoord(0.0f);
	glm::vec3 centerCoord(0.0f);

	vertices.push_back({ glm::vec3(limitXY, 0.0f, 0.0f), color, texCoord });
	vertices.push_back({ glm::vec3(-limitXY, 0.0f, 0.0f), color, texCoord });

	vertices.push_back({ glm::vec3(0.0f, limitXY , 0.0f), color, texCoord });
	vertices.push_back({ glm::vec3(0.0f, -limitXY, 0.0f), color, texCoord });

	vertices.push_back({ glm::vec3(0.0f, 0.0f , limitZ), color, texCoord });
	vertices.push_back({ glm::vec3(0.0f, 0.0f, -limitZ), color, texCoord });

	for (double i = 0.0f; i < limitXY; i+=1.0f) {
		glm::vec3 curCoordLeft(i, 0.0f, 0.5f);
		glm::vec3 curCoordRight(i, 0.0f, -0.5f);
		vertices.push_back({ curCoordLeft, color, texCoord });
		vertices.push_back({ curCoordRight, color, texCoord });
	}

	for (double i = 0.0f; i < limitXY; i+=1.0f) {
		glm::vec3 curCoordLeft(0.0f, i, 0.5f);
		glm::vec3 curCoordRight(0.0f, i, -0.5f);
		vertices.push_back({ curCoordLeft, color, texCoord });
		vertices.push_back({ curCoordRight, color, texCoord });
	}

	for (double i = 0.0f; i < limitZ; i+=1.0f) {
		glm::vec3 curCoordLeft(0.0f, 0.5f, i);
		glm::vec3 curCoordRight(0.0f, -0.5f, i);
		vertices.push_back({ curCoordLeft, color, texCoord });
		vertices.push_back({ curCoordRight, color, texCoord });
	}

	for (double i = 0.0f; i > -limitXY; i -= 1.0f) {
		glm::vec3 curCoordLeft(i, 0.0f, 0.5f);
		glm::vec3 curCoordRight(i, 0.0f, -0.5f);
		vertices.push_back({ curCoordLeft, color, texCoord });
		vertices.push_back({ curCoordRight, color, texCoord });
	}

	for (double i = 0.0f; i > -limitXY; i -= 1.0f) {
		glm::vec3 curCoordLeft(0.0f, i, 0.5f);
		glm::vec3 curCoordRight(0.0f, i, -0.5f);
		vertices.push_back({ curCoordLeft, color, texCoord });
		vertices.push_back({ curCoordRight, color, texCoord });
	}

	for (double i = 0.0f; i > -limitZ; i -= 1.0f) {
		glm::vec3 curCoordLeft(0.0f, 0.5f, i);
		glm::vec3 curCoordRight(0.0f, -0.5f, i);
		vertices.push_back({ curCoordLeft, color, texCoord });
		vertices.push_back({ curCoordRight, color, texCoord });
	}



	for (int i = 0; i < vertices.size(); i++) {
		indices.push_back(i);
		i++;
		indices.push_back(i);
	}


	return Mesh(vertices, indices);
}


