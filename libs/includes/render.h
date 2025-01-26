#ifndef RENDER_H
#define RENDER_H

#include "common.h"

class Render
{
public:
	unsigned int texture;

	void Init();
	void Update();
	void LoadTexture(const char* filename);
};

#endif
