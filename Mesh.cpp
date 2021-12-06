#include "Mesh.h"
#include "EBO.h"

using namespace std;


Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices) {
	this->vertices = vertices;
	this->indices = indices;
	vao.Bind();
	VBO vbo(vertices);
	EBO ebo(indices);
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	vao.Bind();
	camera.Matrix(shader, "camMatrix");
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

