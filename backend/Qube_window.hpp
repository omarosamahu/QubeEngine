#pragma once

#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <GLFW/glfw3.h>
#include <string>

class QubeWindow {
    public:
     QubeWindow(int w,int h,const std::string& name);
     ~QubeWindow();

     QubeWindow(const QubeWindow& other) = delete;
     QubeWindow& operator=(const QubeWindow& other) = delete;

     bool shouldClose() { return glfwWindowShouldClose(window); }

    private:
     void initWindow();
     const int width;
     const int height;
     std::string name;
     GLFWwindow* window;
};