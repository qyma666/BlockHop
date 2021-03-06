//
// Created by Tim on 25/06/2017.
//

#ifndef BLOCKHOP_MOUSEBUTTONSYSTEM_H
#define BLOCKHOP_MOUSEBUTTONSYSTEM_H

#include "../ecs/system.h"

class MouseButtonSystem : public System<MouseButtonSystem>
{
public:
	MouseButtonSystem();
	~MouseButtonSystem();

	std::map<int, int> buttonList;
	bool isButtonPressed(int buttonCode);

	void update(double dt, double alpha);
};

#endif //BLOCKHOP_MOUSEBUTTONSYSTEM_H