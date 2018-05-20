//
// Created by Tim on 25/05/2017.
//
#include "CameraComponent.h"
#include "../ecs/ecsManager.h"
#include <glm/gtc/matrix_transform.hpp>

COMPONENT_EXPORT(CameraComponent, "cameraComponent")

void CameraComponent::setValues(const json &inValues)
{
	//Will throw if incorrect/should automatically be caught by ECSManager
	fov = inValues["fov"].get<float>();
	aspectRatio = inValues["aspectRatio"].get<float>();
	nearDist = inValues["nearDist"].get<float>();
	farDist = inValues["farDist"].get<float>();

	perspective();
}

void CameraComponent::lookAt(glm::vec3 eye, glm::vec3 centre, glm::vec3 up)
{
	viewMatrix = glm::lookAt(eye, centre, up);
}

void CameraComponent::perspective()
{
	projectionMatrix = glm::perspective(fov, aspectRatio, nearDist, farDist);
}

glm::mat4 CameraComponent::getViewMatrix() const { return viewMatrix; }
glm::mat4 CameraComponent::getProjectionMatrix() const { return projectionMatrix; }
