#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window{
public:
    static inline void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    Window();
    ~Window();

    void setViewport();

    void update();
    void endFrame();

    bool shouldClose();
    void setShouldClose(bool shouldClose);

    GLFWwindow* _window;

    static unsigned SCREEN_WIDTH, SCREEN_HEIGHT;

};

#endif