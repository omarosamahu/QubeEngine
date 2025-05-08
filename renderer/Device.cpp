#include <Device.hpp>
#include <algorithm>

/// @brief Checks if the requsted extensions are supported by the physical
/// device
/// @param device
/// @param ppRequestedExtensions
/// @param pequestedExtensionsCounst
/// @return
bool Device::supports(const vk::PhysicalDevice &device,
                      const char **ppRequestedExtensions,
                      const uint32_t pequestedExtensionsCounst)
{
    LOGINFO("Requested physical devices Extentions");
    std::vector<vk::ExtensionProperties> extentions =
        device.enumerateDeviceExtensionProperties().value;

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

uint32_t Device::findQueueFamilyIndex(const vk::PhysicalDevice &device,
                                      const vk::SurfaceKHR &surface,
                                      const vk::QueueFlags queueType)
{
    LOGDEBUG("Finding Queue Family index ...");
    std::vector<vk::QueueFamilyProperties> queueFamilies =
        device.getQueueFamilyProperties();
    /*
    for (size_t i = 0; i < queueFamilies.size(); i++)
    {
        bool supported = false, presented = false;
        vk::QueueFamilyProperties queueFamily = queueFamilies[i];
        if (surface)
        {
            presented = device.getSurfaceSupportKHR(i, surface).result == vk::Result::eSuccess ? true : false;
        }
        else
        {
            presented = false;
        }
        if (queueFamily.queueFlags & queueType)
        {
            supported = true;
        }
        if (supported && presented)
        {
            LOGDEBUG("INDEX ISSSSSSSSSSSSSS: ", i);
            return i;
        }
    }

    return UINT32_MAX;
    */

    int idx = 0;
    if (!surface)
        return UINT32_MAX;
    auto itr =
        std::find_if(queueFamilies.begin(), queueFamilies.end(),
                     [&idx, device, surface, queueType](const vk::QueueFamilyProperties &queueFamily)
                     {
                         bool supported = false, presented = false;
                         presented = device.getSurfaceSupportKHR(idx, surface).result == vk::Result::eSuccess ? true : false;
                         supported = (queueFamily.queueFlags & queueType) ? true : false;
                         ++idx;
                         return (presented & supported);
                     });

    return itr != queueFamilies.end()
               ? static_cast<uint32_t>(std::distance(queueFamilies.begin(), itr))
               : UINT32_MAX;
}

bool Device::is_suitable(const vk::PhysicalDevice &device)
{
    LOGINFO("Checking if the device is suitable ...");

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

vk::PhysicalDevice Device::choose_physical_device(const vk::Instance &instance)
{
    LOGINFO("Choosing physical device ...");
    std::vector<vk::PhysicalDevice> availableDevices =
        instance.enumeratePhysicalDevices().value;
    for (const vk::PhysicalDevice &device : availableDevices)
    {
        // device.getProperties().deviceType == vk::PhysicalDeviceType::eIntegratedGpu
        if (is_suitable(device))
        {
            LOGINFO("Selected device ", device.getProperties().deviceName);
            return device;
        }
    }

    return nullptr;
}

vk::Device Device::create_logical_device(const vk::PhysicalDevice &device, const vk::SurfaceKHR &surface, std::deque<std::function<void(vk::Device)>> &deviceDeletionQueue)
{
    LOGDEBUG("Creating loggical device ...");
    uint32_t graphicsIndex = findQueueFamilyIndex(device, surface, vk::QueueFlagBits::eGraphics);

    vk::PhysicalDeviceFeatures deviceFeatures;
    float queuePriority = 1.0f;

    vk::DeviceQueueCreateInfo queueInfo = vk::DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), graphicsIndex, 1, &queuePriority);
    uint32_t enabled_layer_count = 1;

    std::vector<const char *> enabledLayer{"VK_LAYER_KHRONOS_validation"};

    vk::DeviceCreateInfo deviceInfo = vk::DeviceCreateInfo({},
                                                           1, &queueInfo, enabled_layer_count, enabledLayer.data(),
                                                           0, nullptr, &deviceFeatures);

    vk::ResultValueType<vk::Device>::type logicalDevice = device.createDevice(deviceInfo);
    if (logicalDevice.result == vk::Result::eSuccess)
    {
        deviceDeletionQueue.emplace_back([](vk::Device lDevice)
                                         { lDevice.destroy();
                                        LOGDEBUG("Deleted logical device"); });
        return logicalDevice.value;
    }

    LOGERROR("Failed to create logical device");
    return nullptr;
}
