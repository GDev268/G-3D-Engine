#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

class Texture{
public:
    Texture();
    Texture(const char* path,const char* name,bool defaultParams = true);
    ~Texture() {};
    
    void create();
    void load(bool flip = true);

    void setFilters(GLenum all);
    void setFilters(GLenum mag,GLenum min);

    void setWarp(GLenum all);
    void setWarp(GLenum s,GLenum t);

    void bind();


    int id;
    unsigned int tex;
    const char* name;

    const char* path;
    static int currentID;
    int width,height;
    int nChannels;
};

#endif