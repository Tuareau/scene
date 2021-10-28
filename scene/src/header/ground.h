#pragma once

#ifndef _GROUND_H_
#define _GROUND_H_

#include "figure.h"
#include "color.h"
#include "polygon.h"

namespace tua {

	class Ground : public Figure
	{
	public:
		Ground() = delete;
		Ground(size_t width, size_t length, int y_level, Color color);
		~Ground() = default;

		Figure::FigureType type() const override;
	};

}

#endif