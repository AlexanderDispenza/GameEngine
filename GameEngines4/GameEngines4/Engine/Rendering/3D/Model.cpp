#include "Model.h"

Model::Model(GLuint shaderProgram_) : shaderProgram(0), subMeshes (std::vector<Mesh*>())
{
	
	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
}

Model::~Model()
{
	if (subMeshes.size() > 0) 
	{
		for (auto m : subMeshes) 
		{
			delete m;
			m = nullptr;
		}
	}
}

void Model::Render()
{
	glUseProgram(shaderProgram);
	for (auto m : subMeshes) 
	{
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}
