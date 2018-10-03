#pragma once

#include <exception>
#include <functional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace photochopp {

using coordinate_t = std::pair<uint, uint>;

using pixel_t = std::tuple<uint8_t, uint8_t, uint8_t>;
using pixel_ref_t = std::tuple<uint8_t&, uint8_t&, uint8_t&>;

using pixel_matrix_t = std::vector<std::vector<pixel_ref_t>>;

class Image {
    int channels;
    int width, height;
    size_t size;
    uint8_t* data;
    pixel_matrix_t image;

public:
    Image(const std::string&);

    Image(const Image&);

    Image() = delete;

    ~Image();

    std::pair<uint, uint> get_dimensions() const noexcept { return { width, height }; }

    pixel_t get_pixel(coordinate_t) const;

    void punctual_operation(std::function<pixel_t(pixel_t)>) noexcept;

    void flip_horizontally() noexcept;

    void flip_vertically() noexcept;

    bool write_to_disk(const std::string&) const;
};
}
