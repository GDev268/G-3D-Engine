#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void verifyCompilationShader(unsigned int shader);

   float vertices[] {
        //First Triangle
        -0.15f, 0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.15f,-0.5f,0.0f,

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

    //Starting window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    
    GLFWwindow* window = glfwCreateWindow(1280, 720,"Exercise 01",NULL,NULL);
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

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

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


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

   
    glBindVertexArray(0); 




    while(!glfwWindowShouldClose(window)){

        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, true);
        }

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

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
