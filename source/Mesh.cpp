#include "graphics/Mesh.hpp"

std::vector<Vertex> Vertex::genList(float* vertices, int noVertices)
{
 	std::vector<Vertex> ret(noVertices);

	int stride = sizeof(Vertex) / sizeof(float);

	for (int i = 0; i < noVertices; i++) {
		ret[i].vecPos = glm::vec3(
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		);

		ret[i].texPos = glm::vec2(
			vertices[i * stride + 3],
			vertices[i * stride + 4]
		);
	}

	return ret;
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

void Mesh::render(Shader* shader)
{
    for (unsigned int i = 0; i < textures.size(); i++) {
		shader->setValue(textures[i]->name, textures[i]->id);
		textures[i]->load();
		glBindTexture(GL_TEXTURE_2D, textures[i]->id);
	}

	// EBO stuff
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}

void Mesh::cleanup()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void Mesh::setup()
{
    // create buffers/arrays
	glGenVertexArrays(1, &VAO); // vertex array object
	glGenBuffers(1, &VBO); // vertex buffer object
	glGenBuffers(1, &EBO); // element buffer object

	glBindVertexArray(VAO);

	// load data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// load data into EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set vertex attribute pointers
	// vertex.position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex.texCoord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texPos)));

	glBindVertexArray(0);

}
