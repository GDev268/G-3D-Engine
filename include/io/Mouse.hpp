#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mouse
{
public:
    Mouse();
    ~Mouse();

    
    double getMouseX(); 
    double getMouseY();
    
    double getDX(); 
    double getDY();

    double getScrollDX();
    double getScrollDY();

    bool button(int button);
    bool buttonChanged(int button);
    bool buttonWentUp(int button);
    bool buttonWentDown(int button);

    double x;
    double y;

    double lastX;
    double lastY;

    double dx;
    double dy;

    double scrollDx;
    double scrollDy;

    bool firstMouse;

    bool buttons[GLFW_MOUSE_BUTTON_LAST] = {0};
    bool buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = {0};
};


#endif