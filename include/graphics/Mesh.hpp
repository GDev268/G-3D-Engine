#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

struct Vertex{
    glm::vec3 vecPos;
    glm::vec2 texPos;

    static std::vector<Vertex> genList(float* vertices, int noVertices);
};

typedef struct Vertex Vertex;

class Mesh{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector<Texture*> textures;
    unsigned int VAO;

    Mesh();
    Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture*> textures);
    ~Mesh();

    void render(Shader shader);

    void cleanup();

    unsigned int VBO,EBO;

    void setup();
};

#endif