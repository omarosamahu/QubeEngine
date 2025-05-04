#pragma once


#include <Instance.hpp>
#include <Device.hpp>

class Engine
{
public:
    Engine(QubeWindow *window);
    ~Engine();

private:
    /// @brief Deletion queue
    std::deque<std::function<void(vk::Instance)>> deletionQueue;
    /// @brief Main Window
    QubeWindow *qubeWindow;
    /// @brief Main Instance
    vk::Instance mInstance;
    /// @brief Dynamic instance dispatcher
    vk::DispatchLoaderDynamic dild;
    /// @brief A physical device
    vk::PhysicalDevice phisicalDevice;
    /// @brief Selected Device
    Device dev;
    // vk::PhysicalDeviceType::eDiscreteGpu
};
