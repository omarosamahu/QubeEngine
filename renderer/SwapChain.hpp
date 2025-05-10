#include <common.hpp>

/// @brief description of the surface.
struct SurfaceDetails
{

    /// @brief No of images and supported sizes
    vk::SurfaceCapabilitiesKHR capabilities;

    /// @brief Supported pixal formats
    std::vector<vk::SurfaceFormatKHR> formats;

    /// @brief Available presenetation modes
    std::vector<vk::PresentModeKHR> presentationModes;
};
class SwapChain
{
public:
    void build(
        vk::Device logicalDevice,
        vk::PhysicalDevice physicalDevice,
        const vk::SurfaceKHR &surface,
        const uint32_t width, const uint32_t height,
        std::deque<std::function<void(vk::Device)>> &deviceDeletionQueue);

    /**
     * @brief the number of images
     *
     */
    uint32_t imageCount;

    /**
     * @brief The underlying swapchain resource
     *
     */
    vk::SwapchainKHR chain;

    /**
     * @brief image format
     *
     */
    vk::SurfaceFormatKHR format;

    /**
     * @brief image size
     *
     */
    vk::Extent2D extent;
    private:
        vk::SurfaceFormatKHR choose_surface_format(const std::vector<vk::SurfaceFormatKHR>& format);
        vk::PresentModeKHR choose_present_mode(const std::vector<vk::PresentModeKHR>& presentModes);
        vk::Extent2D choose_extent(uint32_t width, uint32_t height, const vk::SurfaceCapabilitiesKHR &capabilites);

        SurfaceDetails query_surface_support(vk::PhysicalDevice device, const vk::SurfaceKHR &surface);
};