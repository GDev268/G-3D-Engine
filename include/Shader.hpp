#ifndef SHDAER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    public:
    unsigned int id;

    Shader(const char* vertexShaderPath,const char* fragmentShaderPath);
    ~Shader();
    void activate();

    std::string loadShaderSrc(const char* filepath);
    GLuint compileShader(const char* filepath,GLenum type);
    void setMat4(const std::string& name,glm::mat4 value);
    void checkCompilation(GLuint shader);
};


#endif