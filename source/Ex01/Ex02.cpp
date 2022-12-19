#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void verifyCompilationShader(unsigned int shader);

    float triangle1[] {
        //First Triangle
        -0.15f, 0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.15f,-0.5f,0.0f,
    };

    float triangle2[] {
        //Second Triangle
        0.15f, 0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.15f,-0.5f,0.0f,
    };

    const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(0.0f, 0.2f, 0.0f, 0.5f);\n"
    "}\n";

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    
    GLFWwindow* window = glfwCreateWindow(1280, 720,"OpenGL Learning",NULL,NULL);
    if(window == nullptr){
        std::cout << "Failed to load the gl Window!";
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    
    glViewport(0, 0, 1280, 720);

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2,VAOs);
    glGenBuffers(2,VBOs); 

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);

    glCompileShader(vertexShader);

    verifyCompilationShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);

    glCompileShader(fragmentShader);

    verifyCompilationShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 



    while(!glfwWindowShouldClose(window)){

        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, true);
        }

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Swap the buffers
        glfwSwapBuffers(window);
        //Processes the window
        glfwPollEvents();

    }
    glDeleteVertexArrays(1, &VAOs[0]);
    glDeleteBuffers(1, &VBOs[0]);
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAOs[1]);
    glDeleteBuffers(1, &VBOs[1]);

    glfwTerminate();
    return 0;
}

void verifyCompilationShader(unsigned int shader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR WHILE COMPILING THE SHADER!\n" << infoLog;
    }
}