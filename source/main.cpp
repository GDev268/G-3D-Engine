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

unsigned SCREEN_WIDTH = 1280,SCREEN_HEIGHT = 720;
float x,y,z;

std::string loadShaderSrc(const char *filename);

int main()
{
	int success;
	char infoLog[512];
	glm::mat4 trans = glm::mat4(1.0f);
	float test = 0.0f;

	std::cout << "Hello, world!" << std::endl;

	keyboard = new Keyboard();

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Tutorial", NULL, NULL);
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

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetKeyCallback(window, keyCallback);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader *shader = new Shader("assets/shaders/vertex_default.glsl", "assets/shaders/fragment_default.glsl");

	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
		//Positions				//Texture Positions
		-0.5f, -0.5f, -0.5f, 	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 	1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 		1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 		1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 	0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 	0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 		1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 		1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 		1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 		0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 	0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 		1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 	0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 		1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 		1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 		1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 	0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 		0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 		1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 	1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 		1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 		1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 	0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 	0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 		1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 		1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 		1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 		0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 	0.0f, 1.0f
	};

	// VBO, VAO
	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// bind VAO
	glBindVertexArray(VAO);

	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set attributes pointers

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// texture coordinate attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

	glGenTextures(0, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);


	/*data = stbi_load("assets/images/image2.jpg", &width, &height, &nChannels, 0);
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
	glBindTexture(GL_TEXTURE_2D, texture2);*/

	shader->activate();
	shader->setValue("texture1", 0);
	shader->setValue("texture2", 1);

	shader->activate();
	shader->setValue("matrix", trans);

	shader->activate();
	trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setValue("matrix", trans);

	x = 0.0f;
	y = 0.0f;
	z = 3.0f;

	while (!glfwWindowShouldClose(window))
	{
		test += 0.001f;

		// process input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*trans = glm::rotate(trans, glm::radians(test), glm::vec3(test, test, 0.001f));
		shader->activate();
		shader->setValue("matrix", trans);*/

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// draw shapes
		glBindVertexArray(VAO);

		//create transform
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f),glm::vec3(0.5f));
		view = glm::translate(view,glm::vec3(-x,-y,-z));
		projection = glm::perspective(glm::radians(45.0f),(float)SCREEN_WIDTH / SCREEN_HEIGHT,0.1f,100.0f);


		shader->activate();
		shader->setValue("model",model);
		shader->setValue("view",view);
		shader->setValue("projection",projection);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES,0,36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (keyboard->getKey(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
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

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}