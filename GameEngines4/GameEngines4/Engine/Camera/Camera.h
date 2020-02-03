#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRoatation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;

private: 

	void UpdateCameraVector();

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fov, yaw, pitch, nearplane, farplane;
	glm::vec3 forward, up, right, worldUp;



};
#endif


