#include "App.hpp"

App::App(std::unique_ptr<QubeWindow> &window) : window{std::move(window)}
{
}

void App::run()
{
    while (!window->shouldClose())
    {
        glfwPollEvents();
    }
}
