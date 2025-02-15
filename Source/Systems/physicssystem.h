#pragma once

#include "system.h"
#include "gravity.h"
#include "rigidbody.h"
#include "transform.h"
#include "coordinator.h"

class PhysicsSystem : public System
{
public:
	void Init();
	void Update(float dt);
};
