#pragma once
#include <vector>

struct Point 
{
	double x;
	double y;
	double z;

	Point(double x, double y, double z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Sphere 
{
	Point center;
	double radius;
	std::vector<Point> line_start;
	std::vector<Point> line_end;
public:
	Sphere(Point c, double rad) : center(c), radius(rad) { calculateWireframe(); }
	Sphere(const Sphere& s);
	void calculateWireframe();
	std::vector<Point>& getStartPoints() { return line_start; }
	std::vector<Point>& getEndPoints() { return line_end; }
};
