#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include "point.h"

using namespace std;

int main()
{
	vector<tua::Point> points;
	points.emplace_back(00, 01, 02, 03);
	points.emplace_back(00, 11, 12, 13);
	points.emplace_back(00, 21, 22, 23);
	points.emplace_back(00, 31, 32, 33);
	points.emplace_back(00, 01, 02, 03);
	points.emplace_back(00, 11, 12, 13);
	points.emplace_back(00, 21, 22, 23);
	points.emplace_back(00, 31, 32, 33);
	points.emplace_back(00, 01, 02, 03);
	points.emplace_back(00, 11, 12, 13);
	points.emplace_back(00, 21, 22, 23);
	points.emplace_back(00, 31, 32, 33);

	auto less_point{
		[](const auto & lhs, const auto & rhs) {
			return (pow(lhs.x(), 2) + pow(lhs.y(), 2) + pow(lhs.z(), 2)) < 
				(pow(rhs.x(), 2) + pow(rhs.y(), 2) + pow(rhs.z(), 2)); }
	};


	sort(points.begin(), points.end(), less_point);
	auto it = unique(points.begin(), points.end());
	points.erase(it, points.end());

	for (const auto & point : points) {
		cout << "\nPoint: " 
			<< setw(4) << point.x()
			<< setw(4) << point.y()
			<< setw(4) << point.z() 
		<< endl;
	}
}