#include <Device.hpp>

vk::PhysicalDevice Device::choose_physical_device(const vk::Instance &instance)
{
    LOGINFO("Choosing physical device ...");
    auto availableDevices = instance.enumeratePhysicalDevices().value;
    for (const vk::PhysicalDevice &device : availableDevices)
    {
        if (is_suitable(device) && device.getProperties().deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
        {
            LOGINFO("Selected device ", device.getProperties().deviceName);
            return device;
        }
    }

    return nullptr;
}

bool Device::is_suitable(const vk::PhysicalDevice &device)
{
    LOGINFO("Checking if the device is suitable");

    auto ppRequestExtention = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

    if (supports(device, &ppRequestExtention, 1))
    {
        LOGINFO("Device can support the requested extenstion!");
    }
    else
    {
        LOGWARNING("Device can't support the requested extenstion!");
        return false;
    }

    return true;
}

/// @brief Checks if the requsted extensions are supported by the physical device
/// @param device
/// @param ppRequestedExtensions
/// @param pequestedExtensionsCounst
/// @return
bool Device::supports(const vk::PhysicalDevice &device, const char **ppRequestedExtensions, const uint32_t pequestedExtensionsCounst)
{
    LOGINFO("Requested physical devices Extentions");
    auto extentions = device.enumerateDeviceExtensionProperties().value;

    for (size_t i = 0; i < pequestedExtensionsCounst; i++)
    {
        bool supported = false;
        for (const auto &extention : extentions)
        {
            std::string name = extention.extensionName;
            if (name.compare(ppRequestedExtensions[i]) == 0)
            {
                supported = true;
                break;
            }
        }
        if (!supported)
        {
            return false;
        }
    }

    return true;
}
