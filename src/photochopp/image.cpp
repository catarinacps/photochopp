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
    , data((uint8_t*)std::malloc(size + 1))
{
    if (!data) {
        throw std::bad_alloc();
    }

    std::memcpy(data, copy.data, size + 1);
}

Image::~Image()
{
    stbi_image_free(data);
}

std::optional<pixel_t> Image::get_pixel(coordinate_t coordinates) const
{
    auto& [x, y] = coordinates;

    return x < width and y < height ? std::optional{image[y][x]} : std::nullopt;
}

void Image::punctual_operation(std::function<pixel_t(pixel_t)> operation) noexcept
{
    for (auto& line : image) {
        for (auto& pixel : line) {
            auto& [r, g, b] = pixel;

            std::tie(r, g, b) = operation(pixel);
        }
    }
}

void Image::flip_horizontally() noexcept
{
    //TODO: clean up this mess of iterators

    auto front = image.begin();
    auto back = image.rbegin();

    // for every mirror pair of lines in an image
    for (front, back; *front != *back and *(front + 1) != *back; ++front, ++back) {
        std::swap_ranges(front->begin(), front->end(), back->begin());
    }
}

void Image::flip_vertically() noexcept
{
    //TODO: not as messy as the method above, but still, cleaning up required
    
    for (auto& line : image) {
        auto front = line.begin();
        auto back = line.rbegin();

        // for every mirror pair of pixels in a line of pixels
        for (front, back; *front != *back and *(front + 1) != *back; ++front, ++back) {
            front->swap(*back);
        }
    }
}

bool Image::write_to_disk(const std::string& path) const
{
    return stbi_write_jpg(path.c_str(), width, height, channels, data, 100);
}
}
