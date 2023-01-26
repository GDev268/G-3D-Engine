#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "graphics/Mesh.hpp"

class Model{
public:
    std::vector<Mesh*> meshes;

    Model();
    ~Model();

    void init();

    void render(Shader shader);

    void cleanup();
};

#endif