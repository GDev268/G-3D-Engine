#include "Window.hpp"

unsigned Window::SCREEN_WIDTH = 1280,Window::SCREEN_HEIGHT = 720;

Window::Window()
{
	_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Tutorial", NULL, NULL);
	glfwMakeContextCurrent(_window);
}

Window::~Window()
{
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}


void Window::setViewport()
{
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
}

void Window::update()
{
	glClearColor(0.43f, 0.69f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endFrame()
{
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(_window);
}

void Window::setShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(_window,shouldClose);
}
