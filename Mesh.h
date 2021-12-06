#pragma once
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"
#include "Camera.h"

class Mesh {
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	void Draw(Shader& shader, Camera& camera);
private:
	VAO vao;
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
};