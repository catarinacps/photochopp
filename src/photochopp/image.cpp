#include "photochopp/image.hpp"

namespace photochopp {

Image::Image(const std::string& file_name)
    : data(stbi_load(file_name.c_str, &width, &height, &channels, 3))
    , image(height, std::vector<pixel_ref_t>(width))
{
    if (!data) {
        throw std::runtime_error("Image::Image : Bad stbi_load()");
    }

    size = width * height * channels;

    for (uint i = 0; i < height; i++) {
        for (uint j = 0; j < width; j++) {
            auto* pixel = &data[channels * (width * i + j)];
            image[i][j] = { pixel[0], pixel[1], pixel[2] };
        }
    }
}

Image::Image(const Image& copy)
    : channels(copy.channels)
    , width(copy.width)
    , height(copy.height)
    , size(channels * width * height)
    , data((uint8_t*)std::malloc(size))
{
    if (!data) {
        throw std::bad_alloc();
    }

    std::memcpy(data, copy.data, size);
}

Image::~Image()
{
    stbi_image_free(data);
}

pixel_t Image::get_pixel(coordinate_t coordinates) const
{
    auto& [x, y] = coordinates;

    //FIXME: invalid return value when either x or y are invalid
    return x < width and y < height ? image[y][x] : pixel_t({ 0xff, 0xff, 0xff });
}

void Image::punctual_operation(std::function<pixel_t(pixel_t)> operation)
{
    for (auto& line : image) {
        for (auto& pixel : line) {
            auto& [r, g, b] = pixel;

            std::tie(r, g, b) = operation(pixel);
        }
    }
}

bool Image::write_to_disk(const std::string& path) const
{
    return stbi_write_jpg(path.c_str(), width, height, channels, data, 100);
}
}
