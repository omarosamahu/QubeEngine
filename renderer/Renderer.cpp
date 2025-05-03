#include <Renderer.hpp>

Engine::Engine(QubeWindow *window)
{
    mInstance = make_instance("Real Engine", deletionQueue);
}

Engine::~Engine()
{
    while (deletionQueue.size() > 0)
    {
        deletionQueue.back()();
        deletionQueue.pop_back();
    }
}
