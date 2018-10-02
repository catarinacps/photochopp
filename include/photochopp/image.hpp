#pragma once

#include <string>
#include <utility>

#include <CImg.h>

namespace cimg = cimg_library;

class Image {
    cimg::CImg<uint> image;
    std::pair<uint, uint> dimensions;

public:
    /**
     * 
     */
    bool write_to_disk(const std::string& file_name) const;

    std::pair<uint, uint> get_dimensions() const noexcept { return this->dimensions; }

    cimg::CImg<uint>& get_cimg() const noexcept { return this->image; }

    Image(const std::string& file_name);

    Image(const Image& copy);

    Image() = delete;
};