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

void Mesh::Draw(Shader& shader, Camera& camera, GLenum type) {
	shader.Activate();
	vao.Bind();
	camera.Matrix(shader, "camMatrix");
	glDrawElements(type, indices.size(), GL_UNSIGNED_INT, 0);
}

//Mesh::Mesh() {}
//
//
//GraphMesh::GraphMesh(double (*func)(double, double), double limit, double h) :
//	limit(limit)
//{
//	vector<Vertex> res;
//	vector<GLuint> indices;
//	double limitX = limit;
//	double limitY = limit;
//	unsigned int  stepToNext = round(limitX / h);
//
//	posZ = 0.0f;
//	negZ = 0.0f;
//
//	for (double X = -limitX; X < limitX; X += h) {
//		//cout << "YES " << X << "\n";
//		for (double Y = -limitY; Y < limitY; Y += h) {
//			double Z = 0.0f;
//			
//			try {
//				Z = func(X, Y);
//			}
//			catch (out_of_range exp) {
//				//cout << "WTF";
//				continue;
//			}
//			posZ = max(Z, posZ);
//			negZ = max(Z, negZ);
//			glm::vec3 curPos(X, Y, Z);
//			//cout << curPos.x << " " << curPos.y << " " << curPos.z << "\n";
//			glm::vec3 curColor(glm::normalize(curPos));
//			glm::vec2 curTex(0.0f, 0.0f);
//			res.push_back({ curPos, curColor, curTex });
//		}
//	}
//
//
//	//
//	//stepToNext
//	for (unsigned int i = 0; i < (stepToNext * stepToNext - stepToNext); i += stepToNext) {
//		for (unsigned int j = 1; j < stepToNext; j++) {
//			//triangle 1
//
//			indices.push_back(i + j - 1);
//			indices.push_back(i + j);
//			indices.push_back(i + stepToNext + j - 1);
//			//cout << i + j << " " << i + stepToNext + j - 1 << " " << i + stepToNext + j << "\n";
//			//triange 2
//			indices.push_back(i + stepToNext + j - 1);
//			indices.push_back(i + j);
//			indices.push_back(i + stepToNext + j);
//			//cout << i + j - 1 << " " << i + j << " " << i + stepToNext + j << "\n";
//		}
//	}
//
//	for (unsigned int i = stepToNext * stepToNext; i < 2 * (stepToNext * stepToNext - stepToNext); i += stepToNext) {
//		for (unsigned int j = 1; j < stepToNext; j++) {
//			//triangle 1
//
//			indices.push_back(i + j - 1);
//			indices.push_back(i + j);
//			indices.push_back(i + stepToNext + j - 1);
//			//cout << i + j << " " << i + stepToNext + j - 1 << " " << i + stepToNext + j << "\n";
//			//triange 2
//			indices.push_back(i + stepToNext + j - 1);
//			indices.push_back(i + j);
//			indices.push_back(i + stepToNext + j);
//			//cout << i + j - 1 << " " << i + j << " " << i + stepToNext + j << "\n";
//		}
//	}
//
//
//
//
//	//cout << res.size() << endl;
//	graphMesh = Mesh(res, indices);
//	cout << posZ << " " << negZ << "\n";
//	//GenAxis();
//	//vao.Bind();
//	//VBO vbo(vertices);
//	//vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
//	//vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
//	//vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
//	//vao.Unbind();
//	//vbo.Unbind();
//}
//
//void GraphMesh::GenAxis() {
//	glm::vec2 texCoord(0.0f, 0.0f);
//	glm::vec3 color(0.0f, 0.0f, 0.0f);
//	glm::vec3 center(0.0f, 0.0f, 0.0f);
//
//	vertices.push_back({ glm::vec3(-limit, 0.0f, 0.0f), color, texCoord });
//	vertices.push_back({ glm::vec3(limit, 0.0f, 0.0f), color, texCoord });
//	vertices.push_back({ glm::vec3(0.0f, -limit, 0.0f), color, texCoord });
//	vertices.push_back({ glm::vec3(0.0f, limit, 0.0f), color, texCoord });
//
//
//
//}
//
//void GraphMesh::Draw(Shader& shader, Camera& camera) {
//	graphMesh.Draw(shader, camera);
//	//vao.Bind();
//	//glDrawArrays(GL_LINES, 0, 1);
//}
