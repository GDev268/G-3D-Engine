#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard{
public:
    Keyboard();
    ~Keyboard();

    bool getKey(int key);
    bool keyChanged(int key);
    bool keyWentUp(int key);
    bool keyWentDown(int key);

    bool keys[GLFW_KEY_LAST] = {0};
    bool keysChanged[GLFW_KEY_LAST] = {0};
};

#endif