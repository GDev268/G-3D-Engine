#include "io/Mouse.hpp"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

double Mouse::getMouseX()
{
    return x;
}

double Mouse::getMouseY()
{
    return y;
}

double Mouse::getDX()
{
    double _dx = dx;
    // set to 0 because change no longer new
    dx = 0;
    return _dx;
}

double Mouse::getDY()
{
    double _dy = dy;
    // set to 0 because change no longer new
    dy = 0;
    return _dy;
}

double Mouse::getScrollDX()
{
    double _scrollDx = scrollDx;
    // set to 0 because change no longer new
    scrollDx = 0;
    return _scrollDx;
}

double Mouse::getScrollDY()
{
    double _scrollDy = scrollDy;
    // set to 0 because change no longer new
    scrollDy = 0;
    return _scrollDy;
}

bool Mouse::button(int button)
{
    return buttons[button];
}

bool Mouse::buttonChanged(int button)
{
    bool ret = buttonsChanged[button];
    // set to false because change no longer new
    buttonsChanged[button] = false;
    return ret;
}

bool Mouse::buttonWentUp(int button)
{
    return !buttons[button] && buttonChanged(button);
}

bool Mouse::buttonWentDown(int button)
{
    return buttons[button] && buttonChanged(button);
}
