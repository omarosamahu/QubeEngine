#pragma once


#include <Instance.hpp>
#include <Device.hpp>

class Engine
{
public:
    Engine(QubeWindow *window);
    ~Engine();

private:
    /// @brief Instance Deletion queue
    std::deque<std::function<void(vk::Instance)>> instanceDeletionQueue;
    /// @brief Instance Deletion queue
    std::deque<std::function<void(vk::Device)>> deviceDeletionQueue;
    /// @brief Main Window
    QubeWindow *qubeWindow;
    /// @brief Main Instance
    vk::Instance mInstance;
    /// @brief Dynamic instance dispatcher
    vk::DispatchLoaderDynamic dild;
    /// @brief A physical device
    vk::PhysicalDevice physicalDevice;
    /// @brief A physical device
    vk::Device logicalDevice;
    /// @brief Selected Device
    Device mSelectedDevice;
    /// @brief Graphics queue
    vk::Queue graphicsQueue;
    /// @brief Surface to present
    vk::SurfaceKHR surface;
};
