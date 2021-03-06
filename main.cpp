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

double TaskFunction(double X, double Y) {
	double temp = X * Y;
	if (temp < 0) throw out_of_range("Less Than Zero");
	return sqrt(temp);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	modelCube = glm::translate(modelCube, glm::vec3(2.0f, 5.0f, 2.0f));

	//Texture brickTexture("textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	//cout << TaskFunction(-1.0f, 1.0f);

	Cube cube;
	Octaedr octaedr;
	Torus torus = BuildTorus();
	Mesh graph = BuildGraph(TaskFunction, 8.0f, 8.0f, 0.1f);
	Mesh axis = GenerateAxis(8.0f, 8.0f);
	//GraphMesh graph(TaskFunction, 8.0f, 0.1f);
	glm::mat4 modelTorus = glm::mat4(1.0f);
	modelTorus = glm::scale(modelTorus, glm::vec3(1.0f, 1.0f, 1.0f));
	modelTorus = glm::translate(modelTorus, glm::vec3(-5.0f, -5.0f, -5.0f));

	glm::mat4 modelCube1 = glm::mat4(1.0f);
	modelCube1 = glm::scale(modelCube1, glm::vec3(1.0f, 1.0f, 1.0f));
	modelCube1 = glm::translate(modelCube1, glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 modelOctaedr = glm::mat4(1.0f);
	modelOctaedr = glm::scale(modelOctaedr, glm::vec3(2.0f, 2.0f, 2.0f));
	modelOctaedr = glm::translate(modelOctaedr, glm::vec3(5.0f, -5.0f, 5.0f));

	glm::mat4 modelGraph = glm::mat4(1.0f);
	modelGraph = glm::scale(modelGraph, glm::vec3(1.0f, 1.0f, 1.0f));
	//modelOctaedr = glm::translate(modelCube1, glm::vec3(5.0f, -5.0f, 5.0f));
	modelGraph = glm::rotate(modelGraph, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelGraph = glm::rotate(modelGraph, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	Camera camera(width, height, glm::vec3(0.0, 0.0, 2.0));
	
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.8f, 0.1f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::mat4(1.0f);
		shader.Activate();
		camera.Inputs(window);
		camera.UpdateMatrix(45, 1.0f, 100.0f);

		int modelLoc = glGetUniformLocation(shader.ID, "model");

		model = modelCube1;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//cube.Draw(shader, camera);

		model = modelCube;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cube.Draw(shader, camera);

		model = modelOctaedr;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		octaedr.Draw(shader, camera);

		model = modelTorus;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		torus.Draw(shader, camera);

		model = modelGraph;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		graph.Draw(shader, camera);
		axis.Draw(shader, camera, GL_LINES);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}