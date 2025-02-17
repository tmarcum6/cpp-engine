#pragma once

#include "common.h"

class FrameBuffer
{
public:
	FrameBuffer(GLuint width, GLuint height);
	~FrameBuffer();

	GLuint textureId;

	unsigned int getFrameTexture();
	void RescaleFrameBuffer(GLuint width, GLuint height);
	void Bind() const;
	void Unbind() const;

private:
	GLuint m_fbo;
	GLuint m_rbo;
};