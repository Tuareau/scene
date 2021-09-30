#pragma once

#include <tuple>

#include "pixel.h"

namespace tua {
	// left top pixel + width + height
	using Bounds = std::tuple<Pixel, size_t, size_t>;
}
