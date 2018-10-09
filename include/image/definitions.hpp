#pragma once

#include <tuple>
#include <utility>
#include <vector>

namespace image {

using coordinate_t = std::pair<uint, uint>;

using pixel_t = std::tuple<uint8_t, uint8_t, uint8_t>;
using pixel_ref_t = std::tuple<uint8_t&, uint8_t&, uint8_t&>;

using pixel_matrix_t = std::vector<std::vector<pixel_t>>;
}
