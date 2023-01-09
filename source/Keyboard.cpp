#include "Keyboard.hpp"


Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

bool Keyboard::getKey(int key)
{
    return keys[key];
}

bool Keyboard::keyChanged(int key)
{
    bool ret = keysChanged[key];
    keysChanged[key] = false;
    return ret;

}

bool Keyboard::keyWentUp(int key)
{
    return !keys[key] && keyChanged(key);
}

bool Keyboard::keyWentDown(int key)
{
    return keys[key] && keyChanged(key);
}
