#include "depthbuffer.h"

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
				pixels.emplace_back(x, y, std::numeric_limits<int>::min, base_color);
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

	void DepthBuffer::clear() {
		for (const auto & marked_bound : _active_bounds) {
			Bounds bound;
			std::tie(std::ignore, bound) = marked_bound;
			const auto & [pixel, width, height] = bound.as_touple();
			for (size_t x = pixel.x(); x < pixel.x() + width; ++x) {
				std::vector<Pixel> & pixels = _buffer[x];
				for (size_t y = pixel.y(); y < pixel.y() + height; ++y) {
					pixels[y].set_color(_base_color);
					pixels[y].set_depth(INT_MIN);
				}
			}
		}
	}

	void DepthBuffer::draw_figure(const Figure * figure) {
		const auto marked_bounds {
			transform_figure_bounds(figure->bounds(), figure->type())
		};
		if (marked_bounds.first != Figure::FigureType::NONE) {
			const auto index = to_index(figure->type());
			_active_bounds[index] = marked_bounds;
			draw_bound(figure->type());
		}
	}

	void DepthBuffer::draw_bound(Figure::FigureType type) const {
		const auto index = to_index(type);
		const auto & marked_bound = _active_bounds[index];

		Bounds bound;
		std::tie(std::ignore, bound) = marked_bound;
		const auto & [pixel, width, height] = bound;
		for (size_t x = pixel.x(); x < pixel.x() + width; ++x) {
			for (size_t y = pixel.y(); y < pixel.y() + height; ++y) {
				putpixel(x, y, _buffer[x][y].color());
			}
		}
	}

	DepthBuffer::MarkedBounds DepthBuffer::transform_figure_bounds(const Bounds & bound, Figure::FigureType type) {
		const auto & [pixel, width, height] = bound;
		int base_x = pixel.x();
		int base_y = pixel.y();

		if (base_x >= _size.width || base_y >= _size.height) {
			return { std::make_pair(Figure::FigureType::NONE, Bounds()) };
		}
		if (base_x + width <= 0 || base_y + height <= 0) {
			return { std::make_pair(Figure::FigureType::NONE, Bounds()) };
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

		auto transformed_bounds {
			std::make_tuple(Pixel(left_x, top_y, 0), right_x - left_x, bottom_y - top_y)
		};
		return std::make_pair(type, transformed_bounds);
	}

	void DepthBuffer::add_marked_bounds(const MarkedBounds & marked_bound, Figure::FigureType type) {
		const auto index = static_cast<size_t>(type);
		_active_bounds[index] = marked_bound;
	}

}