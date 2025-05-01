#pragma once

#include <Qube_window.hpp>
#include <memory>
class App
{
public:
    App() = default;
    explicit App(std::unique_ptr<QubeWindow>& window);
    void run();

private:
    std::unique_ptr<QubeWindow> window;
};
