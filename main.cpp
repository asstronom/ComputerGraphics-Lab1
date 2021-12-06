#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "StandartObjects.h"

const unsigned int width = 1280;
const unsigned int height = 720;

using namespace std;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	vector<Vertex> cubeVertices = {
		{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, //1
		{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, //2
		{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, //3
		{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, //0
		{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, //1
		{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),glm::vec2(1.0f, 1.0f)}, //2
		{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},//0
	};

	vector<GLuint> indicesCube =
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

	vector<Vertex> octaedrVertices = {
		{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, //0
		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, //1
		{glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, //2
		{glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, //3
		{glm::vec3(0.0f, GLfloat(sqrt(2)), 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.0f, GLfloat(-sqrt(2)), 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
	};

	vector<GLuint> indicesOctaedr = {
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


	GLFWwindow* window = glfwCreateWindow(width, height, "I made this!", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	Shader shader("default.vert", "default.frag");

	glm::mat4 modelCube = glm::mat4(1.0f);
	modelCube = glm::scale(modelCube, glm::vec3(2.0f, 2.0f, 2.0f));
	modelCube = glm::translate(modelCube, glm::vec3(2.0f, 2.0f, 2.0f));

	//Texture brickTexture("textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Mesh cubeMesh(cubeVertices, indicesCube);
	Mesh octaedrMesh(octaedrVertices, indicesOctaedr);

	Cube cube;
	Octaedr octaedr;


	glm::mat4 modelCube1 = glm::mat4(1.0f);
	modelCube1 = glm::scale(modelCube1, glm::vec3(1.0f, 1.0f, 1.0f));
	modelCube1 = glm::translate(modelCube1, glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 modelOctaedr = glm::mat4(1.0f);
	modelOctaedr = glm::scale(modelCube1, glm::vec3(2.0f, 2.0f, 2.0f));
	modelOctaedr = glm::translate(modelCube1, glm::vec3(5.0f, -5.0f, 5.0f));

	Camera camera(width, height, glm::vec3(0.0, 0.0, 2.0));
	
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.8f, 0.1f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::mat4(1.0f);
		shader.Activate();
		camera.Inputs(window);
		camera.UpdateMatrix(45, 1.0f, 450.0f);
		//camera.Matrix(shader, "camMatrix");

		int modelLoc = glGetUniformLocation(shader.ID, "model");

		model = modelCube1;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cubeMesh.Draw(shader, camera);
		cube.Draw(shader, camera);

		model = modelCube;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cubeMesh.Draw(shader, camera);
		cube.Draw(shader, camera);

		model = modelOctaedr;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//octaedrMesh.Draw(shader, camera);
		octaedr.Draw(shader, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}