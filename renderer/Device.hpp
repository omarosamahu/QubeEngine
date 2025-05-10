#pragma once

#include <common.hpp>

class Device
{
public:
    Device() = default;
    ~Device() = default;

    vk::PhysicalDevice choose_physical_device(vk::Instance instance);
    uint32_t findQueueFamilyIndex(vk::PhysicalDevice device,
                                  vk::SurfaceKHR surface,
                                  const vk::QueueFlags queueType);
    vk::Device create_logical_device(
        vk::PhysicalDevice device,
        const vk::SurfaceKHR &surface,
        std::deque<std::function<void(vk::Device)>> &deviceDeletionQueue);
    bool is_suitable(vk::PhysicalDevice device);
    bool supports(vk::PhysicalDevice device,
                  const char **ppRequestedExtensions,
                  const uint32_t pequestedExtensionsCounst);
};
