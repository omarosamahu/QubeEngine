#include <vulkan/vulkan.h>
#include <App.hpp>

int main(int argc, char const *argv[])
{
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    auto window {std::make_unique<QubeWindow>(WIDTH, HEIGHT, "Vulan window!")};
    App qubeApp(window);
    try
    {
        qubeApp.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
