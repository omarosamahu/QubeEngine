#pragma once

#include <common.hpp>

vk::Instance make_instance(const std::string &appName, std::deque<std::function<void(vk::Instance)>> &deleteionQueue);