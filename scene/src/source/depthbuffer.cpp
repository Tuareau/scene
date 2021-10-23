#include "depthbuffer.h"
#include "bounds.h"

namespace tua {

	DepthBuffer::DepthBuffer(size_t width, size_t height, Color base_color) {
		_base_color = base_color;
		_size.width = width;
		_size.height = height;
		_buffer.reserve(width);
		for (size_t x = 0; x < width; ++x) {
			std::vector<Pixel> pixels;
			pixels.reserve(height);
			for (size_t y = 0; y < height; ++y) {
				pixels.emplace_back(x, y);
			}
			_buffer.push_back(std::move(pixels));
		}
	}

	Pixel & DepthBuffer::operator()(size_t x_idx, size_t y_idx) {
		if (x_idx > _buffer.size() || y_idx > _buffer.size()) {
			throw std::out_of_range("DepthBuffer, operator(): trying to reach what is out of bounds");
		}
		return _buffer[x_idx][y_idx];
	}

	size_t DepthBuffer::width() const {	return _size.width;	}

	size_t DepthBuffer::height() const { return _size.height; }

	void DepthBuffer::clear_figure(Figure::FigureType type) {
		const auto idx = to_index(type);
		auto & bounds = _active_bounds[idx];

		const auto & [pixel, width, height] = bounds.as_touple();
		for (size_t x = pixel.x; x < pixel.x + width; ++x) {
			for (size_t y = pixel.y; y < pixel.y + height; ++y) {
				_buffer[x][y].erase_depths(type);
			}
		}
	}

	void DepthBuffer::draw_figure(const MovableFigure & figure) {
		const auto transformed_bounds {
			transform_figure_bounds(figure.bounds())
		};
		const auto index = to_index(figure.type());
		_active_bounds[index] = transformed_bounds;
		draw_bound(transformed_bounds);
	}

	void DepthBuffer::draw_bound(const Bounds & bound) const {
		const auto & [pixel, width, height] = bound.as_touple();
		for (size_t x = pixel.x; x < pixel.x + width; ++x) {
			for (size_t y = pixel.y; y < pixel.y + height; ++y) {
				int color_code = static_cast<int>(_buffer[x][y].nearest_color());
				putpixel(x, y, color_code);
			}
		}
	}

	Bounds DepthBuffer::transform_figure_bounds(const Bounds & bound) {
		const auto & [pixel, width, height] = bound.as_touple();
		int base_x = pixel.x;
		int base_y = pixel.y;

		if (base_x >= int(_size.width) || base_y >= int(_size.height)) {
			return Bounds();
		}
		if (base_x + width <= 0 || base_y + height <= 0) {
			return Bounds();
		}

		auto left_x = base_x;
		auto right_x = base_x + width;
		auto top_y = base_y;
		auto bottom_y = base_y + height;

		if (left_x < 0) {
			left_x = 0;
		}
		if (right_x > _size.width) {
			right_x = _size.width;
		}

		if (top_y < 0) {
			top_y = 0;
		}
		if (bottom_y > _size.height) {
			bottom_y = _size.height;
		}

		Vec2 pt = {
			left_x,
			top_y,
		};
		auto new_width = right_x - left_x;
		auto new_height = bottom_y - top_y;
		return Bounds(pt, new_width, new_height);
	}

	size_t tua::to_index(typename Figure::FigureType type) {
		return static_cast<size_t>(type);
	}

}