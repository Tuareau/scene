#include "figure.h"
namespace tua {

	void Figure::fill_matrix()
	{
		std::set<Point *> figure_points;
		for (auto & polygon : _polygons) {
			for (size_t i = 0; i < polygon.size(); ++i)
				figure_points.insert(polygon[i]);
		}
		std::vector<Point *> points(figure_points.begin(), figure_points.end());
		_figure_matrix = new Matrix(points);
	}

	Figure::~Figure() {
		delete _figure_matrix;
	}
}