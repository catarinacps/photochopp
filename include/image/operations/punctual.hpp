#pragma once

#include "image/definitions.hpp"

namespace image {

namespace operations {

    uint8_t calculate_luminance(pixel_t pixel);

    pixel_t convert_to_greyscale(pixel_t pixel);
}
}
