#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "common.h"

int main()
{
    Window window;
    window.Init("Engine", window.SCR_WIDTH, window.SCR_HEIGHT);

    Renderer renderer;

    while (!window.ShouldClose())
    {
        window.ProcessEvents();
        window.init_ImGui();
        renderer.Update();
        window.shader->Use();
        window.Render();
        window.render_ImGui();
        window.Update();
    }

    window.close_ImGui();
    window.Shutdown();
    return 0;
}

#endif