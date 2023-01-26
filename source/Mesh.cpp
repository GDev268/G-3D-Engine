#include "graphics/Mesh.hpp"

std::vector<Vertex> Vertex::genList(float* vertices, int noVertices)
{
    std::vector<Vertex> ret(noVertices);

    int stride = sizeof(Vertex) / sizeof(float);

    for(int i = 0;i < noVertices;i++){
        //Put the first three coordinates AKA: the vertex pos
        ret[i].vecPos = glm::vec3(
            vertices[i * stride + 0],
            vertices[i * stride + 1],
            vertices[i * stride + 2]
        );

        //Put the last two coordinates AKA: the texture pos
        ret[i].texPos = glm::vec2(
            vertices[i * stride + 3],
            vertices[i * stride + 4]
        );
    }
    
    return ret;
}

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures):
vertices(vertices),indices(indices),textures(textures)
{
    setup();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    
    for(unsigned int i = 0;i < textures.size();i++){
        delete textures[i];
    }

}

void Mesh::render(Shader shader)
{
    for(unsigned int i = 0;i < textures.size();i++){
        shader.setValue(textures[i]->name,textures[i]->id);
        textures[i]->bind();
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::cleanup()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void Mesh::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);

    //set vertex attribute pointers
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(Vertex), (void*)offsetof(Vertex,vecPos));
	glEnableVertexAttribArray(0);

    //texture coordinate attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(Vertex), (void*)offsetof(Vertex,texPos));
	glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}
