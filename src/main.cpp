#include <vulkan/vulkan.h>
#include <App.hpp>
#include <thread>
#include <atomic>
#include <Renderer.hpp>
#include <Logger.hpp>

void spawn_render_thread(QubeWindow *window, std::atomic<bool> *done)
{
    auto engine = std::make_unique<Engine>(window);
    while (!*done)
    {
        /* code */
    }
}

int main(int argc, char const *argv[])
{
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    QubeWindow window{WIDTH, HEIGHT, "Vulan window!"};

    App qubeApp(&window);
    std::atomic<bool> done;
    std::thread render_thread(spawn_render_thread, &window, &done);
    auto logger = Logger::getInstance();
    try
    {
        qubeApp.run();
    }
    catch (const std::exception &e)
    {
    }

    done = true;
    render_thread.join();

    return 0;
}
