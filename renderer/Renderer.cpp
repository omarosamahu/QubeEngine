#include <Renderer.hpp>

Engine::Engine(QubeWindow *window) : qubeWindow{window}
{
    LOGINFO("Initialize engine");
    mInstance = make_instance("Real Engine", deletionQueue);
    dild = vk::DispatchLoaderDynamic(mInstance, vkGetInstanceProcAddr);
    phisicalDevice = mSelectedDevice.choose_physical_device(mInstance);
}

Engine::~Engine()
{
    LOGINFO("Goodbye!!!");
    while (deletionQueue.size() > 0)
    {
        deletionQueue.back()(mInstance);
        deletionQueue.pop_back();
    }
}
