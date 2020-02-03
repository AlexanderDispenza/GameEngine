#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:
	GameObject(Model* model_);
	~GameObject();
	
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

private:
	Model* model;

};

#endif

