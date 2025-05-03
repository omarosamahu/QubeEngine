#pragma once


#include <Instance.hpp>

class Engine
{
public:
    Engine(QubeWindow *window);
    ~Engine();

private:
    std::deque<std::function<void()>> deletionQueue;
    vk::Instance mInstance;
};
