#pragma once

#include <common.hpp>

class QubeInstance
{
public:
    QubeInstance() = default;
    ~QubeInstance() = default;

    QubeInstance(const QubeInstance &) = delete;
    QubeInstance &operator=(const QubeInstance &) = delete;
    vk::Instance make_instance(const std::string &appName, std::deque<std::function<void(vk::Instance)>> &deleteionQueue);
};