#include <common.hpp>


class Frame{
    public:
        explicit Frame(const vk::Image& image);
        ~Frame() = default;
        private:
            vk::Image mImage;
};