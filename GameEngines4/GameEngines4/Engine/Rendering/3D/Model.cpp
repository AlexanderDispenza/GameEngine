#include "Model.h"

Model::Model()
{
	subMeshes = std::vector<Mesh*>();
	subMeshes.reserve(10);
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
	for (auto m : subMeshes) 
	{
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}
