#include <SwapChain.hpp>
#include <cmath>

void SwapChain::build(const vk::Device &logicalDevice, const vk::PhysicalDevice &physicalDevice, const vk::SurfaceKHR &surface, const uint32_t width, const uint32_t height, std::deque<std::function<void(vk::Device)>> &deviceDeletionQueue)
{
    auto support = query_surface_support(physicalDevice, surface);
    format = choose_surface_format(support.formats);
    LOGINFO("Supported format: ", static_cast<uint32_t>(format.format));
    extent = choose_extent(width, height, support.capabilities);
    auto presentMode = choose_present_mode(support.presentationModes);
    LOGINFO("Present mode: ", static_cast<uint32_t>(presentMode));


    uint32_t image_count = std::min(support.capabilities.maxImageCount, support.capabilities.maxImageCount + 1);

    vk::SwapchainCreateInfoKHR swapChainInfo({}, surface, image_count, format.format, format.colorSpace, extent, 1,
                                             vk::ImageUsageFlagBits::eColorAttachment, vk::SharingMode::eExclusive);

    swapChainInfo.preTransform = support.capabilities.currentTransform;
    swapChainInfo.presentMode = presentMode;
    swapChainInfo.clipped = VK_TRUE;
    swapChainInfo.oldSwapchain = vk::SwapchainKHR(nullptr);

    auto result = logicalDevice.createSwapchainKHR(swapChainInfo);
    if (result.result != vk::Result::eSuccess)
    {
        LOGERROR("Failed to create swapchain");
        return;
    }

    chain = result.value;
    deviceDeletionQueue.emplace_back([this](const vk::Device &device)
                                     { device.destroy(chain); });
}

vk::SurfaceFormatKHR SwapChain::choose_surface_format(const std::vector<vk::SurfaceFormatKHR> &formats)
{
    auto itr = std::find_if(formats.begin(), formats.end(), [](const vk::SurfaceFormatKHR &format)
                            { return (format.format == vk::Format::eB8G8R8A8Unorm && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear); });
    return itr != formats.end() ? *itr : formats[0];
}

vk::PresentModeKHR SwapChain::choose_present_mode(const std::vector<vk::PresentModeKHR> &presentModes)
{
    auto itr = std::find_if(presentModes.begin(), presentModes.end(), [](const vk::PresentModeKHR &mode)
                            { return mode == vk::PresentModeKHR::eMailbox; });
    return itr != presentModes.end() ? *itr : vk::PresentModeKHR::eFifo;
}

vk::Extent2D SwapChain::choose_extent(uint32_t width, uint32_t height, const vk::SurfaceCapabilitiesKHR &capabilites)
{
    if (capabilites.currentExtent.width != UINT32_MAX)
    {
        return capabilites.currentExtent;
    }

    vk::Extent2D extent;

    extent.width = std::min(capabilites.maxImageExtent.width, std::max(width, capabilites.currentExtent.width));
    extent.height = std::min(capabilites.maxImageExtent.height, std::max(height, capabilites.currentExtent.height));

    return extent;
}

SurfaceDetails SwapChain::query_surface_support(const vk::PhysicalDevice &device, const vk::SurfaceKHR &surface)
{
    LOGDEBUG("Check if the surface can support ...");
    SurfaceDetails support;
    support.capabilities = device.getSurfaceCapabilitiesKHR(surface).value;
    support.formats = device.getSurfaceFormatsKHR(surface).value;
    support.presentationModes = device.getSurfacePresentModesKHR(surface).value;

    return support;
}
