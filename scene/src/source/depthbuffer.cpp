#include "depthbuffer.h"

namespace tua {

	DepthBuffer::DepthBuffer(size_t width, size_t height, int base_color) : _base_color(base_color) {
		_size.width = width;
		_size.height = height;
		_screen_map.reserve(width);
		for (size_t x = 0; x < width; ++x) {
			std::vector<Pixel> pixels;
			pixels.reserve(height);
			for (size_t y = 0; y < height; ++y)
				pixels.emplace_back(x, y, INT_MIN, base_color);
			_screen_map.push_back(std::move(pixels));
		}
	}

	Pixel & DepthBuffer::operator()(size_t x_idx, size_t y_idx) {
		if (x_idx > _screen_map.size() || y_idx > _screen_map.size())
			throw std::out_of_range("DepthBuffer, operator(): trying to reach what is out of bounds");
		return _screen_map[x_idx][y_idx];
	}

	size_t DepthBuffer::width() const {	return _size.width;	}

	size_t DepthBuffer::height() const { return _size.height; }

	void DepthBuffer::clear() {
		for (size_t x = 0; x < _screen_map.size(); ++x) {
			std::vector<Pixel> & pixels = _screen_map[x];
			for (size_t y = 0; y < pixels.size(); ++y) {
				pixels[y].set_color(_base_color);
				pixels[y].set_depth(INT_MIN);
			}
		}
	}

	void DepthBuffer::draw(const Bounds & bounds) const {
		const auto & [pixel, width, height] = bounds;
		if (pixel.x() < 0 || pixel.y() < 0)
			return;
		if (pixel.x() + width > _screen_map.size())
			return;
		if (pixel.y() + height > _screen_map[0].size())
			return;

		const auto x_bound = pixel.x() + width;
		const auto y_bound = pixel.y() + height;
		for (size_t x = pixel.x(); x < x_bound; ++x) {
			const std::vector<Pixel> & pixels = _screen_map[x];
			for (size_t y = pixel.y(); y < y_bound; ++y)
				putpixel(x, y, pixel.color());
		}
	}


	void tua::DepthBuffer::SHOW_DEPTHS() const
	{
		std::cout << "\n\nDEPTHS:\n\n";
		for (size_t x = 0; x < _screen_map.size(); ++x) {
			const std::vector<Pixel> & pixels = _screen_map[x];
			for (size_t y = 0; y < pixels.size(); ++y)
				std::cout << pixels[y].depth() << "\n";
			std::cout << std::endl;
		}

	}

	void tua::DepthBuffer::SHOW_COLORS() const
	{
		std::cout << "\n\nCOLORS:\n\n";
		for (size_t x = 0; x < _screen_map.size(); ++x) {
			const std::vector<Pixel> & pixels = _screen_map[x];
			for (size_t y = 0; y < pixels.size(); ++y)
				std::cout << pixels[y].color() << "\n";
			std::cout << std::endl;
		}
	}
}