#include "image/operations/punctual.hpp"

namespace image {

namespace operations {

    uint8_t calculate_luminance(pixel_t pixel)
    {
        auto [r, g, b] = pixel;

        return 0.299 * r + 0.578 * g + 0.114 * b;
    }

    pixel_t convert_to_greyscale(pixel_t pixel)
    {
        auto luminance = calculate_luminance(pixel);

        return { luminance, luminance, luminance };
    }
}
}
