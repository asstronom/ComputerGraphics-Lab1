#pragma once
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"
#include "Camera.h"

class Mesh {
public:
	//Mesh();
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	void virtual Draw(Shader& shader, Camera& camera);
	void virtual Draw(Shader& shader, Camera& camera, GLenum type);
private:
	VAO vao;
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
};

//class GraphMesh {
//public:
//	GraphMesh(double (*func)(double, double), double limit, double precision);
//	void Draw(Shader& shader, Camera& camera);
//	void GenAxis();
//private:
//	std::vector<Vertex> vertices;
//	double posZ;
//	double negZ;
//	double limit;
//	Mesh graphMesh;
//	VAO vao;
//};
