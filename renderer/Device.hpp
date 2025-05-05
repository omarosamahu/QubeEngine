#pragma once

#include <common.hpp>

class Device
{
public:
    Device() = default;
    ~Device() = default;

    vk::PhysicalDevice choose_physical_device(const vk::Instance &instance);
    vk::Device create_logical_device(
        const vk::PhysicalDevice &device,
        std::deque<std::function<void(vk::Device)>> &deviceDeletionQueue);
    bool is_suitable(const vk::PhysicalDevice &device);
    bool supports(const vk::PhysicalDevice &device,
                  const char **ppRequestedExtensions,
                  const uint32_t pequestedExtensionsCounst);
    uint32_t findQueueFamilyIndex(const vk::PhysicalDevice &device,
                                  const vk::QueueFlags queueType);
};
