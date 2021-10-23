#include "pixel.h"
#include "figure.h"

namespace tua {

	Pixel::Pixel(size_t x, size_t y)
		: _x(x), _y(y) {}

	size_t Pixel::x() const { return _x; }

	size_t Pixel::y() const { return _y; }

	void Pixel::push_depth(const Depth & depth) {
		const auto & equal {
			std::find_if(_depths.begin(), _depths.end(),
				[&depth](const auto & existing_depth) {
					return depth.z == existing_depth.z;
				}
			)
		};
		if (equal != _depths.end()) {
			equal->color = depth.color;
			equal->object_type = depth.object_type;
			return;
		}

		const auto & greater {
			std::find_if(_depths.begin(), _depths.end(),
				[&depth](const auto & existing_depth) {
					return depth.z > existing_depth.z;
				}
			)
		};
		_depths.insert(greater, depth);
	}

	Depth & Pixel::operator[](size_t idx) {
		return _depths[idx];
	}

	const Depth & Pixel::operator[](size_t idx) const {
		return _depths[idx];
	}

	void Pixel::erase_depths(Figure::FigureType type) {
		auto removed = std::remove_if(_depths.begin(), _depths.end(),
			[&type](const auto & depth) { return depth.object_type == type; });
		_depths.erase(removed, _depths.end());
	}

	Color Pixel::nearest_color() const {
		if (_depths.empty()) {
			return Color::BLACK;
		}
		else {
			return _depths.front().color;
		}
	}
}