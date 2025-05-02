#include <App.hpp>

App::App(QubeWindow *window) : window{window}
{
}

void App::run()
{
    while (!window->shouldClose())
    {
        glfwPollEvents();
    }
}
