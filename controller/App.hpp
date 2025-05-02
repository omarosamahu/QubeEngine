#pragma once

#include <QubeWindow.hpp>
// #include <Logger.hpp>

class App
{
public:
    App() = default;
    explicit App(QubeWindow *window);
    void run();

private:
    QubeWindow *window;
};
