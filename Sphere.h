#pragma once
#include <vector>

struct Point 
{
	float x;
	float y;
	float z;

	Point(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Sphere 
{
	Point center;
	float radius;
	int lat;
	int lon;
	std::vector<Point> line_start;
	std::vector<Point> line_end;
public:
	Sphere(Point c, float rad) : center(c), radius(rad), lat(16), lon(8) { calculateWireframe(); }
	Sphere(const Sphere& s);
	void calculateWireframe();
	std::vector<Point>& getStartPoints() { return line_start; }
	std::vector<Point>& getEndPoints() { return line_end; }
};