#include <QubeWindow.hpp>

QubeWindow::QubeWindow(int w, int h, const std::string &name) : width{w}, height{h}, name{name}
{
    initWindow();
}

QubeWindow::~QubeWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    LOGINFO("Destroying the window");
}

void QubeWindow::initWindow()
{
    // initialize glfw library
    glfwInit();
    // Tell glfw not to create opengl context
    // This is done by using GLFW_NO_API
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Tell glfw not to resize the the window
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (window)
    {
        LOGINFO("Successfully make a window ", name, " Width: ", width, " Height: ", height);
    }
    else
    {
        LOGERROR("Glfw Window created failed");
    }
}
