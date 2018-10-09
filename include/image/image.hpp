#pragma once

#include "image/definitions.hpp"

#include <cstring>
#include <exception>
#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace image {

class Image {
    int channels;
    int width = 0, height = 0;
    size_t size;
    uint8_t* data;
    pixel_matrix_t image;

public:
    Image(const std::string&);

    Image(const Image&);

    Image() = delete;

    ~Image();

    std::pair<uint, uint> get_dimensions() const noexcept { return { width, height }; }

    std::optional<pixel_t> get_pixel(coordinate_t) const noexcept;

    void apply_operation(std::function<pixel_t(pixel_t)>);

    std::vector<uint> quantize(std::function<uint8_t(pixel_t)>);

    void flip_vertically() noexcept;

    void flip_horizontally() noexcept;

    bool write_to_disk(const std::string&) const;
};
}
