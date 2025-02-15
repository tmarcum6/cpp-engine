#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "window.h"
#include "renderer.h"
#include "framebuffer.h"

int main()
{
    Window window;
    window.init("Engine", window.SCR_WIDTH, window.SCR_HEIGHT);

    while (!window.shouldClose())
    {
        window.processEvents();
        window.initImGui();
        window.renderImGui();
        window.bindFrameBuffer();
        window.updateRenderer();
        window.useShader();
        window.handleTransformations();
        window.unbindFrameBuffer();
        window.update();
    }

    window.closeImGui();
    window.shutDown();
    return 0;
}

#endif