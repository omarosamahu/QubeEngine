#pragma once

#include <common.hpp>

class Device
{
public:
    Device() = default;
    ~Device() = default;

    vk::PhysicalDevice choose_physical_device(const vk::Instance &instance);
    bool is_suitable(const vk::PhysicalDevice &device);
    bool supports(const vk::PhysicalDevice &device, const char **ppRequestedExtensions, const uint32_t pequestedExtensionsCounst);
};
