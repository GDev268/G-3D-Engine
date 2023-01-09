#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Keyboard.hpp"

inline void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
Keyboard *keyboard;
glm::mat4 mouseTransform = glm::mat4(1.0f);
float testAlpha = 0.0f;

std::string loadShaderSrc(const char *filename);

int main()
{
	int success;
	char infoLog[512];
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 trans2 = glm::mat4(1.0f);
	float test = 0.0f;

	std::cout << "Hello, world!" << std::endl;

	keyboard = new Keyboard();

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

	glfwSetKeyCallback(window, keyCallback);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader *shader = new Shader("assets/shaders/vertex_default.glsl", "assets/shaders/fragment_default.glsl");

	float vertices[] = {
		// positions		// colors			// texture coordinates
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 0.75f, 0.0f, 1.0f, // top left
		0.5f, -0.5f, 0.0f, 0.6f, 1.0f, 0.2f, 1.0f, 0.0f,  // bottom right
		0.5f, 0.5f, 0.0f, 1.0f, 0.2f, 1.0f, 1.0f, 1.0f	  // top right
	};
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		3, 1, 2	 // second triangle
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Texture
	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// load image
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("assets/images/image1.jpg", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: IMAGE FAILED TO LOAD!";
	}

	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("assets/images/image2.png", &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: IMAGE FAILED TO LOAD!";
	}

	stbi_image_free(data);
	shader->activate();
	shader->setValue("texture1", 0);
	shader->setValue("texture2", 1);

	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	shader->activate();
	shader->setValue("matrix", trans);

	while (!glfwWindowShouldClose(window))
	{
		test += 0.001f;
		// process input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		trans = glm::rotate(trans, glm::radians(test), glm::vec3(test, test, 0.001f));
		shader->activate();
		shader->setValue("matrix", trans);

		shader->activate();
		shader->setValue("alpha", testAlpha);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// draw shapes
		glBindVertexArray(VAO);
		shader->activate();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

	if (keyboard->getKey(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (keyboard->getKey(GLFW_KEY_KP_ADD))
	{
		if (testAlpha <= 1.0f)
		{
			testAlpha += 0.01f;
		}
	}

	if (keyboard->getKey(GLFW_KEY_KP_SUBTRACT))
	{
		if (testAlpha >= 0.0f)
		{
			testAlpha += -0.01f;
		}
	}
}

inline void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!keyboard->keys[key])
		{
			keyboard->keys[key] = true;
		}
	}
	else
	{
		keyboard->keys[key] = false;
	}

	keyboard->keysChanged[key] = action != GLFW_REPEAT;
}