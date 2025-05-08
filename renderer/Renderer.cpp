#include <Renderer.hpp>

Engine::Engine(QubeWindow *window) : qubeWindow{window}
{
    LOGINFO("Initialize engine");
    mInstance = make_instance("Real Engine", instanceDeletionQueue);
    dild = vk::DispatchLoaderDynamic(mInstance, vkGetInstanceProcAddr);

    VkSurfaceKHR rawSurface;
    glfwCreateWindowSurface(mInstance, qubeWindow->getWindow(), nullptr, &rawSurface);

    surface = rawSurface;

    instanceDeletionQueue.emplace_back([this](vk::Instance instance)
                                       {LOGDEBUG("Deleting Surface"); 
                                        mInstance.destroySurfaceKHR(surface); });

    physicalDevice = mSelectedDevice.choose_physical_device(mInstance);
    logicalDevice = mSelectedDevice.create_logical_device(physicalDevice, surface, deviceDeletionQueue);

    uint32_t graphicsIndex = mSelectedDevice.findQueueFamilyIndex(physicalDevice, surface, vk::QueueFlagBits::eGraphics);
    graphicsQueue = logicalDevice.getQueue(graphicsIndex, 0); // 0 represensts the front of the queue family
}

Engine::~Engine()
{
    LOGINFO("Goodbye!!!");
    while (deviceDeletionQueue.size() > 0)
    {
        deviceDeletionQueue.back()(logicalDevice);
        deviceDeletionQueue.pop_back();
    }

    while (instanceDeletionQueue.size() > 0)
    {
        instanceDeletionQueue.back()(mInstance);
        instanceDeletionQueue.pop_back();
    }
}
