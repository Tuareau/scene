#pragma once

#ifndef _BOUNDS_H_
#define _BOUNDS_H_

#include <tuple>
#include <vector>

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

		enum class State { SET, UNSET };
		State _state;

		/*static const int BOUND_ERROR = 5;*/

	public:
		Bounds();
		Bounds(const Vec2 & base, size_t width, size_t height);

		Bounds(const Bounds & other);
		Bounds & operator=(const Bounds & other);

		//Bounds fit(size_t width, size_t height) const;
		Bounds compose(const Bounds & other);
		std::vector<Bounds> split(size_t count) const;
		bool empty() const;

		bool is_set() const;

		std::tuple<Vec2, size_t, size_t> as_touple() const;

	};

	Bounds make_bounds(const Vec2 & base, size_t width, size_t height);

}

#endif