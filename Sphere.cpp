#include <cmath>
#include "Sphere.h"
#include <fstream>

double DEGS_TO_RAD = 3.14159f / 180.0f;

Sphere::Sphere(const Sphere& s) : center(s.center.x, s.center.y, s.center.z)
{
	this->radius = s.radius;
	this->lat = 16;
	this->lon = 8;
	this->line_start = s.line_start;
	this->line_end = s.line_end;
}

void Sphere::calculateWireframe()
{
	int p, s;
	double x, y, z, out;
	int nPitch = lon + 1;

	double pitchInc = (180.0f / (double)nPitch) * DEGS_TO_RAD;
	double rotInc = (360.0f / (double)lat) * DEGS_TO_RAD;
	double y_old = center.y + radius;

	double *x_old_points = new double[lat];
	double *z_old_points = new double[lat];

	double *x_new_points = new double[lat];
	double *z_new_points = new double[lat];

	for (p = 1; p < nPitch; p++)
	{
		out = radius * sin((double)p * pitchInc);
		if (out < 0) 
			out = -out;
		y = radius * cos(p * pitchInc);
		bool f = false;
		double x_old = 0, z_old = 0;

		for (s = 0; s < lat + 1; s++)
		{
			x = out * cos(s * rotInc);
			z = out * sin(s * rotInc);

			x_old_points[s] = x;
			z_old_points[s] = z;

			if (f == true) {
				line_start.push_back(Point((x_old + center.x), (y + center.y), (z_old + center.z)));
				line_end.push_back(Point((x + center.x), (y + center.y), (z + center.z)));
			}

			f = true;

			x_old = x;
			z_old = z;
		}

		if (p == 1) {
			for (int i = 0; i < lat; i++) {
				x_new_points[i] = 0.0;
				z_new_points[i] = 0.0;
			}
		}

		for (int i = 0; i < lat; i++) {
			line_start.push_back(Point((x_old_points[i] + center.x), (y + center.y), (z_old_points[i] + center.z)));
			line_end.push_back(Point((x_new_points[i] + center.x), (y_old), (z_new_points[i] + center.z)));

		}

		for (int i = 0; i < lat; i++) {
			x_new_points[i] = x_old_points[i];
			z_new_points[i] = z_old_points[i];
		}

		y_old = y + center.y;
	}

	y_old = center.y - radius;
	for (int i = 0; i < lat; i++) {
		x_new_points[i] = 0.0;
		z_new_points[i] = 0.0;
	}
	for (int i = 0; i < lat; i++) {
		line_start.push_back(Point((x_old_points[i] + center.x), (y + center.y), (z_old_points[i] + center.z)));
		line_end.push_back(Point((x_new_points[i] + center.x), (y_old), (z_new_points[i] + center.z)));
	}
}
