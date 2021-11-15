#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "Libraries/include/glm/glm.hpp"
#include "Libraries/include/glm/gtc/matrix_transform.hpp"
#include "Libraries/include/glm/gtc/type_ptr.hpp"
#include "shaderClass.h"


int main() {
	//HWND console_window = GetConsoleWindow();
	//ShowWindow(console_window, false);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.6f, 0.6f, 0.0f, // 0
		-0.6f, 0.4f, 0.0f, // 1
		-0.4f, 0.4f, 0.0f, // 2
		-0.4f, 0.6f, 0.0f, // 3
		-0.2f, 0.7f, 0.0f,  // 4
		-0.2f, 0.6f, 0.0f, // 5
		-0.4f, 0.5f, 0.0f, // 6
		-0.4f, 0.0f, 0.0f, // 7
		0.0f, 0.0f, 0.0f, // 8
		-0.2f, 0.25f, 0.0f, // 9
		0.3f, 0.25f, 0.0f, // 10
		0.3f, -0.4f, 0.0f, // 11
		0.3f, 0.45f, 0.0f, // 12
		0.5f, 0.25f, 0.0f, // 13
		0.5f, 0.45f, 0.0f, // 14
		0.3f, 0.0f, 0.0f, // 15
		0.6f, -0.4f, 0.0f, //16
		0.3f, -0.8f, 0.0f, // 17
		-0.6f, 0.0f, 0.0f, // 18
		-0.6f, -0.2f, 0.0f, //19
		-0.25f, -0.2f, 0.0f, //20
		-0.25f, 0.0f, 0.0f, // 21
		-0.8f, -0.2f, 0.0f, //22
		-0.1f, 0.0f, 0.0f //23
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 3, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		10, 13, 14,
		15, 16, 17,
		18, 19, 20,
		18, 20, 21,
		18, 19, 22,
		20, 21, 23
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "I made this!", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	Shader shader("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint transformLoc = glGetUniformLocation(shader.ID, "transform");

	glm::mat4 transform = glm::mat4(1.0f);

	//glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	GLuint lenIndeces = sizeof(indices) / sizeof(GLfloat);

	VAO1.Bind();
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.8f, 0.1f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glDrawElements(GL_TRIANGLES, lenIndeces, GL_UNSIGNED_INT, 0);
		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
			transform = glm::scale(transform, glm::vec3(0.99, 0.99, 0.0));
		}
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
			transform = glm::scale(transform, glm::vec3(1.01, 1.01, 0.0));
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(0.0f, 0.005f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(0.0f, -0.005f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(0.005f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			transform = glm::translate(transform, glm::vec3(-0.005f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			transform = glm::rotate(transform, glm::radians(3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			transform = glm::rotate(transform, glm::radians(-3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
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