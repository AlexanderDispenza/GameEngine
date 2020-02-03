#include "Model.h"

Model::Model(GLuint shaderProgram_, glm::vec3 position_, 
	float angle_, glm::vec3 rotation_, glm::vec3 scale_) : subMeshes(std::vector<Mesh*>())
{
	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;

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

void Model::Render(Camera* camera_)
{
	glUseProgram(shaderProgram);
	for (auto m : subMeshes)
	{
		m->Render(camera_, GetTransform());
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}

glm::vec3 Model::GetPosition() const
{
	return position;
}

glm::vec3 Model::GetRotation() const
{
	return rotation;
}

float Model::GetAngle() const
{
	return angle;
}

glm::vec3 Model::GetScale() const
{
	return scale;
}

glm::mat4 Model::GetTransform() const
{
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	
	return model;
}

void Model::SetPosition(glm::vec3 pos_)
{
	position = pos_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}

void Model::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	
}

void Model::SetScale(glm::vec3 scale_)
{
	scale = scale_;
}
