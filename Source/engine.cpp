#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "window.h"
#include "renderer.h"
#include "framebuffer.h"

int main()
{
    Window window;
    window.Init("Engine", window.SCR_WIDTH, window.SCR_HEIGHT);

    while (!window.ShouldClose())
    {
        window.ProcessEvents();
        window.init_ImGui();
        window.render_ImGui();
        window.bindFrameBuffer();
        window.updateRenderer();
        window.useShader();
        window.handleTransformations();
        window.unbindFrameBuffer();
        window.Update();
    }

    window.close_ImGui();
    window.Shutdown();
    return 0;
}

#endif