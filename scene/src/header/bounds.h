#pragma once

#include <tuple>

#include "pixel.h"
#include "size.h"

namespace tua {

	class Bounds
	{
	private:
		Pixel _base;
		Size _size;

	public:
		Bounds();
		Bounds(const Pixel & base, size_t width, size_t height);

		Bounds(const Bounds & other);
		Bounds & operator=(const Bounds & other);

		Bounds fit(size_t width, size_t height) const;
		Bounds compose(const Bounds & other);

		friend bool are_crossed(const Bounds & b1, const Bounds & b2);

		std::tuple<Pixel, size_t, size_t> as_touple() const;

	};

	Bounds make_bounds(const Pixel & base, size_t width, size_t height) {
		return Bounds(base, width, height);
	}

}
