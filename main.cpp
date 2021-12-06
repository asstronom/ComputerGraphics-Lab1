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

const unsigned int width = 1280;
const unsigned int height = 720;

int main() {
	//HWND console_window = GetConsoleWindow();
	//ShowWindow(console_window, false);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	//-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	// 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	// 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	//};


	GLfloat verticesCube[] =
	{
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //1
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, //2
		-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //3
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //0
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //1
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //2
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, //3
	};

	GLuint indicesCube[] =
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

	GLfloat verticesOctaedr[]{
		0.0f, 0.0f, 1.0f,        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //0
		1.0f, 0.0f, 0.0f,       0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //1
		0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
		-1.0f, 0.0f, 0.0f,       1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //3
		0.0f, GLfloat(sqrt(2)), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, GLfloat(-sqrt(2)), 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	};

	GLuint indicesOctaedr[]{
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

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(verticesCube, sizeof(verticesCube));
	EBO EBO1(indicesCube, sizeof(indicesCube));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glm::mat4 modelCube = glm::mat4(1.0f);
	modelCube = glm::scale(modelCube, glm::vec3(2.0f, 2.0f, 2.0f));
	modelCube = glm::translate(modelCube, glm::vec3(2.0f, 2.0f, 2.0f));

	
	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(verticesCube, sizeof(verticesCube));
	EBO EBO2(indicesCube, sizeof(indicesCube));

	VAO2.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	glm::mat4 modelCube1 = glm::mat4(1.0f);
	modelCube1 = glm::scale(modelCube1, glm::vec3(1.0f, 1.0f, 1.0f));
	modelCube1 = glm::translate(modelCube1, glm::vec3(0.0f, 0.0f, 0.0f));

	VAO VAO3;
	VAO3.Bind();

	VBO VBO3(verticesOctaedr, sizeof(verticesOctaedr));
	EBO EBO3(indicesOctaedr, sizeof(indicesOctaedr));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	glm::mat4 modelOctaedr = glm::mat4(1.0f);
	modelOctaedr = glm::scale(modelCube1, glm::vec3(2.0f, 2.0f, 2.0f));
	modelOctaedr = glm::translate(modelCube1, glm::vec3(5.0f, -5.0f, 5.0f));

	GLuint modelLoc = glGetUniformLocation(shader.ID, "model");

	glm::mat4 model = glm::mat4(1.0f);
	

	//glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	GLuint lenIndecesCube = sizeof(indicesCube) / sizeof(GLfloat);
	GLuint lenIndecesOctaedr = sizeof(indicesOctaedr) / sizeof(GLfloat);

	Texture brickTexture("textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	VAO1.Bind();


	Camera camera(width, height, glm::vec3(0.0, 0.0, 2.0));

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.8f, 0.1f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

		VAO1.Bind();
		EBO1.Bind();
		model = modelCube;
		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, lenIndecesCube, GL_UNSIGNED_INT, 0);

		VAO2.Bind();
		EBO2.Bind();
		model = modelCube1;
		modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, lenIndecesCube, GL_UNSIGNED_INT, 0);

		VAO3.Bind();
		EBO3.Bind();
		model = modelOctaedr;
		modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, lenIndecesOctaedr, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}