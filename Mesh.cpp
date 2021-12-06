#include "Mesh.h"
#include "EBO.h"

using namespace std;


Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices) {
	this->vertices = vertices;
	this->indices = indices;
	vao.Bind();
	VBO vbo(vertices);
	EBO ebo(indices);
	
}

