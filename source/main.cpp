#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
std::string loadShaderSrc(const char *filename);

int main()
{
	int success;
	char infoLog[512];
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 trans2 = glm::mat4(1.0f);
	float test = 0.0f;

	std::cout << "Hello, world!" << std::endl;

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1280, 720, "OpenGL Tutorial", NULL, NULL);
	if (window == NULL)
	{ // window not created
		std::cout << "Could not create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 1280, 720);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader* shader = new Shader("assets/shaders/vertex_default.glsl","assets/shaders/fragment_default.glsl");
	Shader* shader2 = new Shader("assets/shaders/vertex_default.glsl","assets/shaders/fragment_core_2.glsl");


	float vertices[] = {
		//Positions              //Colors
	   -0.25f, -0.5f, 0.0f,   	 1.0f,1.0f,0.5f,
		0.15f, 0.0f, 0.4f,       0.5f,1.0f,0.75f,
		0.0f, 0.5f, -0.2f,		 0.6f,1.0f,0.2f,
		0.5f, -0.4f, 0.2f,       1.0f,0.2f,1.0f
	};
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		3, 1, 2  // second triangle
	};

	
	// VBO, VAO, EBO
	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	// bind VAO
	glBindVertexArray(VAO);

	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// put index array in EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set attributes pointers
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shader->activate();
	shader->setMat4("matrix",trans);

	trans2 = glm::rotate(trans2, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	shader2->activate();
	shader2->setMat4("matrix",trans2);

	while (!glfwWindowShouldClose(window))
	{
		test += 0.01f;
		// process input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		trans = glm::translate(trans, glm::vec3(0.0001f, 0.0001f, 0.0001f));
		shader->activate();
		shader->setMat4("matrix",trans);

		trans2 = glm::translate(trans2, glm::vec3(-0.0001f, -0.0001f, -0.0001f));
		shader2->activate();
		shader2->setMat4("matrix",trans2);

		trans = glm::rotate(trans, glm::radians(test), glm::vec3(sin(0.1), 0.1f, 0.1f));
		shader->activate();
		shader->setMat4("matrix",trans);
		trans2 = glm::rotate(trans2, glm::radians(test), glm::vec3(0.0f, -0.2f, -0.1f));
		shader2->activate();
		shader2->setMat4("matrix",trans2);

		// draw shapes
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		shader->activate();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		shader2->activate();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

std::string loadShaderSrc(const char *filename)
{
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";

	file.open(filename);

	if (file.is_open())
	{
		buf << file.rdbuf();
		ret = buf.str();
	}
	else
	{
		std::cout << "Could not open " << filename << std::endl;
	}

	file.close();

	return ret;
}