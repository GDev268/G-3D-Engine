#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main()
{

    // glm experimentation
    glm::vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f); // identity matrix
    //trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); //Translation (Movement)
    trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0f,0.0f,1.0f)); //Rotation
    //trans = glm::scale(trans,glm::vec3(0.5f,0.5f,0.5f));
    vec = trans * vec; // Must put the translation befor the vector

    std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "OpenGL Learning", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to load the gl Window!";
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        // Swap the buffers
        glfwSwapBuffers(window);
        // Processes the window
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true);
        }
                                  
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
