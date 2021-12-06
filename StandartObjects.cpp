#include "StandartObjects.h"

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
