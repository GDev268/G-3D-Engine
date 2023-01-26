#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "io/Keyboard.hpp"
#include "io/Mouse.hpp"
#include "io/Camera.hpp"
#include "Window.hpp"
#include "graphics/models/Cube.hpp"

inline void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

inline void cursorPosCallback(GLFWwindow *window, double _x, double _y);
inline void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
inline void mouseWheelCallback(GLFWwindow* window,double dx,double dy);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(double dt);

Keyboard *keyboard;
Mouse *mouse;
Window* window;

Camera *camera = new Camera(glm::vec3(2.0f, 0.0f, 0.3f));
float deltaTime = 0.0f;
float lastFrame = 0.0f;

double lastX;
double lastY;

unsigned SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
float x, y, z;
float angle;

std::string loadShaderSrc(const char *filename);

int main()
{
	int success;
	char infoLog[512];
	glm::mat4 trans = glm::mat4(1.0f);
	float test = 0.0f;

	std::cout << "Hello, world!" << std::endl;

	keyboard = new Keyboard();
	mouse = new Mouse();

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = new Window();

	if(window == nullptr){
		std::cout << "Could not create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	window->setViewport();

	glfwSetKeyCallback(window->_window, keyCallback);

	glfwSetCursorPosCallback(window->_window, cursorPosCallback);
	glfwSetMouseButtonCallback(window->_window, mouseButtonCallback);
	glfwSetScrollCallback(window->_window, mouseWheelCallback);

	glfwSetFramebufferSizeCallback(window->_window, framebuffer_size_callback);
	glfwSetInputMode(window->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader *shader = new Shader("assets/shaders/vertex_default.glsl", "assets/shaders/fragment_default.glsl");

	Cube* cube = new Cube(glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.75f));
	cube->init();

	while (!window->shouldClose())
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		test += 1.0f;

		window->update();

		// process input
		processInput(deltaTime);

		// create transform
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = camera->getViewMatrix();
		projection = glm::perspective(glm::radians(camera->zoom), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

		shader->activate();
		shader->setValue("view", view);
		shader->setValue("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		window->endFrame();
	}

	glfwTerminate();
	return 0;
}

void processInput(double dt)
{
	if (keyboard->getKey(GLFW_KEY_ESCAPE))
	{
		window->setShouldClose(true);
	}

	if (keyboard->getKey(GLFW_KEY_W))
	{
		camera->updatePosition(CameraDirection::FOWARD, dt);
	}
	if (keyboard->getKey(GLFW_KEY_S))
	{
		camera->updatePosition(CameraDirection::BACKWARD, dt);
	}
	if (keyboard->getKey(GLFW_KEY_D))
	{
		camera->updatePosition(CameraDirection::RIGHT, dt);
	}

	if (keyboard->getKey(GLFW_KEY_A))
	{
		camera->updatePosition(CameraDirection::LEFT, dt);
	}

	if (keyboard->getKey(GLFW_KEY_SPACE))
	{
		camera->updatePosition(CameraDirection::UP, dt);
	}

	if (keyboard->getKey(GLFW_KEY_LEFT_SHIFT))
	{
		camera->updatePosition(CameraDirection::DOWN, dt);
	}

	double dx = mouse->getDX(),dy = mouse->getDY();
	if(dx != 0 || dy != 0){
		camera->updateDirection(dx,dy);
	}

	double scrollDy = mouse->getScrollDY();
	if(scrollDy != 0){
		camera->updateZoom(scrollDy);
	}
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
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

void cursorPosCallback(GLFWwindow *window, double _x, double _y)
{
	mouse->x = _x;
	mouse->y = _y;

	if (mouse->firstMouse)
	{
		mouse->lastX = mouse->x;
		mouse->lastY = mouse->y;
		mouse->firstMouse = false;
	}

	mouse->dx = mouse->x - mouse->lastX;
	mouse->dy = mouse->lastY - mouse->y; // y coordinates are inverted
	mouse->lastX = mouse->x;
	mouse->lastY = mouse->y;
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!mouse->buttons[button])
		{
			mouse->buttons[button] = true;
		}
	}
	else
	{
		mouse->buttons[button] = false;
	}
	mouse->buttonsChanged[button] = action != GLFW_REPEAT;
}

void mouseWheelCallback(GLFWwindow* window,double dx,double dy){
	mouse->scrollDx = dx;
	mouse->scrollDy = dy;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}