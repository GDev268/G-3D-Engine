#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShaderSrc(const char* filename);

int main() {
	int success;
	char infoLog[512];
	glm::mat4 trans = glm::mat4(1.0f);
	float test = 0.0f;

	std::cout << "Hello, world!" << std::endl;

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Tutorial", NULL, NULL);
	if (window == NULL) { // window not created
		std::cout << "Could not create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 1280, 720);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// compile vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderSrc = loadShaderSrc("assets/shaders/vertex_core.glsl");
	const GLchar* vertShader = vertShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	// catch error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error with vertex shader comp.:" << std::endl << infoLog << std::endl;
	}

	// compile fragment shader
	unsigned int fragmentShaders[2];

	fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragShaderSrc = loadShaderSrc("assets/shaders/fragment_core.glsl");
	const GLchar* fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[0]);

	// catch error
	glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
		std::cout << "Error with fragment shader comp.:" << std::endl << infoLog << std::endl;
	}

	fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragShaderSrc = loadShaderSrc("assets/shaders/fragment_core_2.glsl");
	fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[1]);

	// catch error
	glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
		std::cout << "Error with fragment shader 2 comp.:" << std::endl << infoLog << std::endl;
	}

	// shader program
	unsigned int shaderPrograms[2];

	shaderPrograms[0] = glCreateProgram();

	glAttachShader(shaderPrograms[0], vertexShader);
	glAttachShader(shaderPrograms[0], fragmentShaders[0]);
	glLinkProgram(shaderPrograms[0]);

	// catch errors
	glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
		std::cout << "Linking error:" << std::endl << infoLog << std::endl;
	}

	shaderPrograms[1] = glCreateProgram();

	glAttachShader(shaderPrograms[1], vertexShader);
	glAttachShader(shaderPrograms[1], fragmentShaders[1]);
	glLinkProgram(shaderPrograms[1]);

	// catch errors
	glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
		std::cout << "Linking error:" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaders[0]);
	glDeleteShader(fragmentShaders[1]);

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

	//positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Colors
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	trans = glm::rotate(trans,glm::radians(45.0f),glm::vec3(0.0f,0.0f,1.0f));
	glUseProgram(shaderPrograms[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0],"matrix"),1,GL_FALSE,glm::value_ptr(trans));

	while (!glfwWindowShouldClose(window)) {
		test += 0.01f;
		// process input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw shapes
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderPrograms[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/*glUseProgram(shaderPrograms[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(float)));
		glBindVertexArray(0);*/


		trans = glm::translate(trans,glm::vec3(0.0001f,0.0001f,0.0001f));
		glUseProgram(shaderPrograms[0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0],"matrix"),1,GL_FALSE,glm::value_ptr(trans));

		trans = glm::rotate(trans,glm::radians(test),glm::vec3(sin(0.1),0.1f,0.1f));
		glUseProgram(shaderPrograms[0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0],"matrix"),1,GL_FALSE,glm::value_ptr(trans));



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

std::string loadShaderSrc(const char* filename) {
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";

	file.open(filename);

	if (file.is_open()) {
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		std::cout << "Could not open " << filename << std::endl;
	}

	file.close();

	return ret;
}