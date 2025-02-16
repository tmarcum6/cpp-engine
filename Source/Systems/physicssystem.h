#pragma once

#include "System.h"
#include "Gravity.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Coordinator.h"

class PhysicsSystem : public System
{
public:
	void Init();
	void Update(float dt);
};
