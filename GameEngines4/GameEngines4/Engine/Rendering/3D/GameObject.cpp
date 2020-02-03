#include "GameObject.h"

GameObject::GameObject(Model* model_) : model(nullptr)
{
	model = model_;
}

GameObject::~GameObject()
{
	if (model) 
	{
		delete model;
	}
	model = nullptr;
}

void GameObject::Render(Camera* camera_)
{
	if (model)
	{
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime_)
{
	if (model) 
	{
		// rotate model overtime 
		model->SetAngle(model->GetAngle() + 0.005f);
	}
}
