//
// Created by Tim on 25/05/2017.
//

#include <GLFW/glfw3.h>
#include "MouseInputSystem.h"
#include "../ecs/ecsManager.h"
#include "../window.h"
#include "../components/TransformComponent.h"
#include "../components/MouseControlComponent.h"

SYSTEM_EXPORT(MouseInputSystem, "mouseInputSystem")

extern Window* window;
void mouseMoveInputEvent(GLFWwindow *window, double xpos, double ypos);

MouseInputSystem::MouseInputSystem()
{
	glfwSetCursorPosCallback(window->glfwWindow, mouseMoveInputEvent);
}
MouseInputSystem::~MouseInputSystem() {}

void MouseInputSystem::update(double dt, double alpha)
{
	/*
	updateSystemTriggers();

	for(auto entity : getEntities())
	{
		updateEntityTriggers(entity);

		//XComponent* x = entity->getComponent<XComponent>();
	}*/
}

glm::vec2 MouseInputSystem::getLastPos() const
{
	return lastPos;
}

void MouseInputSystem::setLastPos(glm::vec2 inLastPos)
{
	lastPos = inLastPos;
}

void mouseMoveInputEvent(GLFWwindow *window, double xpos, double ypos)
{
	MouseInputSystem* mouseSystem = ECSManager::get().findSystem<MouseInputSystem>();
	glm::vec2 lastPos = mouseSystem->getLastPos();
	if(lastPos.x == 0 && lastPos.y == 0)
		lastPos = glm::vec2(xpos, ypos);

	double pitch = (lastPos.y - ypos)/100.0f;
	double yaw = (lastPos.x - xpos)/100.0f;

	for(auto entity : mouseSystem->getEntities())
	{
		auto transform = entity->getComponent<TransformComponent>();
		auto mouseControl = entity->getComponent<MouseControlComponent>();

		glm::quat rotation = transform->getRotation();
		glm::quat y = glm::angleAxis((float) (-yaw*(mouseControl->getXSensitivity()/100)), glm::vec3(0,1,0));
		glm::quat p = glm::angleAxis((float) (pitch*(mouseControl->getYSensitivity()/100)), transform->getRight());
		rotation *= p*y;
		transform->setRotation(rotation);
	}

	mouseSystem->setLastPos(glm::vec2(xpos, ypos));
}