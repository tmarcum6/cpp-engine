#pragma once

#include "System.h"
#include "Shader.h"
#include "Camera.h"
#include "Renderable.h"
#include "Transform.h"
#include "Coordinator.h"
#include "Shader.h"
#include <cmath>
#include <memory>

class Event;

class RenderSystem : public System
{
public:
	void Init();
	void Update(float dt);

private:
	void WindowSizeListener(Event& event) const;

	std::unique_ptr<Shader> shader;
	Entity mCamera;
	GLuint mVao{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
};
