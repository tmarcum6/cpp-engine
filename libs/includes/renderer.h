#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"

class Renderer
{
public:
	unsigned int texture;

	void Init();
	void Update();
	void LoadTexture(const char* filename);
};

#endif
