#pragma once

#include "System.h"
#include "Transform.h"
#include "Coordinator.h"

class Event;

class CameraControlSystem : public System
{
public:
	void Init();
	void Update(float dt);

	float speed = 20.0f;

private:
	std::bitset<8> mButtons;

	void InputListener(Event& event);
};
