//
// Created by Tim on 25/05/2017.
//

#ifndef BLOCKHOP_MOUSEINPUTSYSTEM_H
#define BLOCKHOP_MOUSEINPUTSYSTEM_H

#include "../ecs/system.h"
#include <glm/vec2.hpp>

class MouseInputSystem : public System
{
	static bool exported;
	glm::vec2 lastPos;

public:
	MouseInputSystem();
	~MouseInputSystem();

	glm::vec2 getLastPos() const;
	void setLastPos(glm::vec2 inLastPos);

	void update(double dt);
};

#endif //BLOCKHOP_MOUSEINPUTSYSTEM_H