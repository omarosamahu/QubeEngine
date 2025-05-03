#include <Instance.hpp>
#include <Logger.hpp>

vk::Instance make_instance(const std::string &appName, std::deque<std::function<void()>> &deleteionQueue)
{
    // auto logger = Logger::getInstance();
    // std::string msg = "Making an instance...";
    LOGINFO("Making an instance...");
    auto version = vk::enumerateInstanceVersion().value;
    vk::ApplicationInfo appInfo(appName.c_str(), version, nullptr, version, version);

    uint32_t glfwExtentionCount = 0;

    auto glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);
    if (glfwExtentions == nullptr)
    {
        throw std::invalid_argument("Failed to get required GLFW Vulkan extensions!");
    }
    std::cout << "Extentions to be requested\n";

    for (size_t i{0U}; i < glfwExtentionCount; ++i)
    {
        std::cout << glfwExtentions[i] << "\n";
    }

    vk::InstanceCreateInfo createInfo({}, &appInfo,
                                      0, nullptr, // No layers introduced yet
                                      glfwExtentionCount, glfwExtentions);
    vk::ResultValue<vk::Instance> instanceAttempt = vk::createInstance(createInfo);
    if (instanceAttempt.result != vk::Result::eSuccess)
    {
        throw std::invalid_argument("Failed to create vulkan Instance!");
    }
    vk::Instance instance = instanceAttempt.value;
    VkInstance handle = instanceAttempt.value;

    deleteionQueue.push_back([handle]()
                             { vkDestroyInstance(handle, nullptr); 
                            std::cout << "Deleted instance\n"; });
    return instance;
}