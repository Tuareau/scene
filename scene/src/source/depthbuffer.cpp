#include "depthbuffer.h"

namespace tua {

	DepthBuffer::DepthBuffer(size_t width, size_t height, int base_color) 
		: _base_color(base_color) 
	{
		_size.width = width;
		_size.height = height;
		_buffer.reserve(width);
		for (size_t x = 0; x < width; ++x) {
			std::vector<Pixel> pixels;
			pixels.reserve(height);
			for (size_t y = 0; y < height; ++y)
				pixels.emplace_back(x, y, INT_MIN, base_color);
			_buffer.push_back(std::move(pixels));
		}
	}

	Pixel & DepthBuffer::operator()(size_t x_idx, size_t y_idx) {
		if (x_idx > _buffer.size() || y_idx > _buffer.size())
			throw std::out_of_range("DepthBuffer, operator(): trying to reach what is out of bounds");
		return _buffer[x_idx][y_idx];
	}

	size_t DepthBuffer::width() const {	return _size.width;	}

	size_t DepthBuffer::height() const { return _size.height; }

	void DepthBuffer::clear() {
		for (const auto & rect : _used_bounds) {
			const auto & [pixel, width, height] = rect;
			for (size_t x = pixel.x(); x < pixel.x() + width; ++x) {
				std::vector<Pixel> & pixels = _buffer[x];
				for (size_t y = pixel.y(); y < pixel.y() + height; ++y) {
					pixels[y].set_color(_base_color);
					pixels[y].set_depth(INT_MIN);
				}
			}
		}
		_used_bounds.erase(_used_bounds.begin(), _used_bounds.end());
	}

	void DepthBuffer::draw(const Bounds & bound) {
		transform_and_add_bound(bound);
		const auto & [pixel, width, height] = _used_bounds.back();
		for (size_t x = pixel.x(); x < pixel.x() + width; ++x) {
			for (size_t y = pixel.y(); y < pixel.y() + height; ++y)
				putpixel(x, y, _buffer[x][y].color());
		}
	}

	void DepthBuffer::transform_and_add_bound(const Bounds & bound) {
		const auto & [pixel, width, height] = bound;
		int base_x = pixel.x();
		int base_y = pixel.y();

		if (base_x > _size.width || base_y > _size.height)
			return;
		if (base_x + width < 0 || base_y + height < 0)
			return;

		size_t finite_x, finite_y;
		if (base_x < 0) {
			finite_x = size_t(width + base_x);
			base_x = 0;
		}
		else {
			finite_x = size_t(base_x + width);
			if (finite_x > _size.width)
				finite_x = _size.width;
		}
		if (base_y < 0) {
			finite_y = size_t(height + base_y);
			base_y = 0;
		}
		else {
			finite_y = size_t(base_y + height);
			if (finite_y > _size.height)
				finite_y = _size.height;
		}

		const auto & used_bound {
			std::make_tuple(Pixel(base_x, base_y, 0), finite_x - base_x, finite_y - base_y)
		};
		_used_bounds.push_back(used_bound);
	}

}