#pragma once

#ifndef _BOUNDS_H_
#define _BOUNDS_H_

#include <tuple>

#include "size.h"

namespace tua {

	struct Vec2 {
		int x;
		int y;
	};

	class Bounds
	{
	private:
		Vec2 _base;
		Size _size;

	public:
		Bounds();
		Bounds(const Vec2 & base, size_t width, size_t height);

		Bounds(const Bounds & other);
		Bounds & operator=(const Bounds & other);

		//Bounds fit(size_t width, size_t height) const;
		//Bounds compose(const Bounds & other);
		bool empty() const;

		//friend bool are_crossed(const Bounds & b1, const Bounds & b2);

		std::tuple<Vec2, size_t, size_t> as_touple() const;

	};

	Bounds make_bounds(const Vec2 & base, size_t width, size_t height);

}

#endif