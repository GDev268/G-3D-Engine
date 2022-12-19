#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(){

    float vertices1[] = {
        -1.5f,-1.5f,0.0f, //-> Top Point
        1.5f,-1.75f,0.0f,
        0.0f,2.0f,0.0f
    };

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

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


    //Vertex buffer objects storage
    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // ============================ VERTEX SHADER ============================

    //Vertex Shader source for the triangle
    const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


    //Shader initialization
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    //Insert the shader source in the shader
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    
    //Shader compilation
    glCompileShader(vertexShader);

    //Verify if the shader is compiled
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR WHILE COMPILING THE SHADER!\n" << infoLog;
    }

// ============================ FRAGMENT SHADER ============================

    const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(0.0f, 0.2f, 0.0f, 0.5f);\n"
    "}\n";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Insert the shader source in the shader
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    
    //Shader compilation
    glCompileShader(fragmentShader);

    //Verify if the shader is compiled
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR WHILE COMPILING THE SHADER!\n" << infoLog;
    }

// ============================ SHADER PROGRAM ============================

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR WHILE COMPILING THE SHADER!\n" << infoLog;
    }

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);

    /*glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); */ 

    while(!glfwWindowShouldClose(window)){
        //Swap the buffers
        glfwSwapBuffers(window);
        //Processes the window
        glfwPollEvents();

        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, true);
        }


        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);*/
    }

    glfwTerminate();
    return 0;
}
