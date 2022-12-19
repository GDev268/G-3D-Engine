#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(){

    GLfloat red = 0.0f;
    GLfloat green = 0.0f;
    GLfloat blue = 0.0f;


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500,500,"Healthy is a nerd",NULL,NULL);
    if(window == nullptr){
        std::cout << "Failed to load the gl Window!";
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window)){
        //Swap the buffers
        glfwSwapBuffers(window);
        //Processes the window
        glfwPollEvents();

        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, true);
        }
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        red += 0.001;
        green += 0.005;
        blue += 0.015;

        if(red >= 1){
            red = 0;
        }  
        if(green >= 1){
            green = 0;
        }        
        if(blue >= 1){
            blue = 0;
        }

    }

    glfwTerminate();
    return 0;
}
