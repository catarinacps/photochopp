#include "photochopp/image.hpp"

Image::Image(const std::string& file_name)
    : image(file_name.c_str())
    , dimensions{ this->image.width(), this->image.height() }
{
}