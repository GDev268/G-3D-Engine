#include "graphics/Model.hpp"

Model::Model()
{

}

Model::~Model()
{

}

void Model::init()
{
}

void Model::render(Shader shader)
{
    for(Mesh* curMesh : meshes){
        curMesh->render(shader);
    }
}

void Model::cleanup()
{
    for(Mesh* curMesh : meshes){
        curMesh->cleanup();
    }
}
