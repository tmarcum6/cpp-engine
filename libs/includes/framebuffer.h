#pragma once

#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

class FrameBuffer
{
public:
	FrameBuffer(float width, float height);
	~FrameBuffer();

	GLuint textureId;

	unsigned int getFrameTexture();
	void RescaleFrameBuffer(float width, float height);
	void Bind() const;
	void Unbind() const;

private:
	GLuint m_fbo;
	GLuint m_rbo;
};