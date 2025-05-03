#pragma once

#include <vulkan/vulkan.hpp>
#include <functional>
#include <deque>
#include <QubeWindow.hpp>

vk::Instance make_instance(const std::string &appName, std::deque<std::function<void()>> &deleteionQueue);